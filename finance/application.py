import os

import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached: https://www.codebyamir.com/blog/a-web-developers-guide-to-browser-caching
# All browsers attempt to keep local copies of static assets in an effort to reduce page load times and minimize network traffic. e.g JS, CSS
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get 1 row of each symbol, since there may be many of the same symbol in purachase table
    # get values for SYMBOL and SHARES
    try:
        rows = db.execute("SELECT symbol, SUM(shares) FROM purchases WHERE userID = :id GROUP BY symbol", id=session['user_id'])
        # print(rows)

        # get values for PRICE and TOTAL and GRANDTOTAL
        grandtotal = 0

        for row in rows:

            price = lookup(row["symbol"])["price"]
            total = price * int(row["SUM(shares)"])
            row["price"] = usd(price)
            row["total"] = usd(total)
            # maybe use round(number, ndigits) to round off to 2 decimal places ??
            # add these new key-value pairs to the dictionary row; it is easier to render the values by just passing in 1 variable called 'rows' into index.html,
            # rather than passing in 'rows', 'prices' and 'totals' as it complicates the for loop in index.html

            grandtotal = grandtotal + total

        # get value for CASH
        cashrow = db.execute("SELECT cash FROM users WHERE id = :id", id=session['user_id'])
        cash = cashrow[0]["cash"]

        grandtotal = grandtotal + cash
        # PLEASE use usd() to format ALL values displayed! check50 checks this
        return render_template("index.html", rows=rows, cash=usd(cash), grandtotal=usd(grandtotal))

    except:
        return apology("Oops, something went wrong", 400)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":

        # handle user's input, check50 tests for SERVER-side validification
        # use lookup() because I want to check if that symbol exists, there will be no such symbol if no result is returned form lookup()

        if not lookup(request.form.get("symbol")) or not request.form.get("shares"):
            return apology("Please fill in the blanks", 400)

        # this try solves the error: ValueError: invalid literal for int() with base 10: '1.5'
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Invalid number of shares", 400)

        if int(request.form.get("shares")) <= 0 or not request.form.get("shares").isdigit():
            return apology("Invalid number of shares", 400)

        symbol = request.form.get("symbol")

        # lookup price
        result = lookup(symbol)
        # check if user has enough cash
        usercash = db.execute("SELECT cash FROM users WHERE id = :id", id=session['user_id'])
        # usd() changes type from float to str
        topay = shares * result["price"]
        if topay > usercash[0]["cash"]:
            return apology("Sorry, you have insufficient cash", 400)

        # SQL tables: numeric precision refers to the maximum number of digits in the number, scale refers to max no. of decimal places
        # deduct shares*price from user's cash, update users table
        db.execute("UPDATE users SET cash = cash - :topay WHERE id = :id", topay=topay, id=session['user_id'])

        # insert row into purchase table WHO bought WHAT at what PRICE and WHEN
        db.execute("INSERT INTO purchases (symbol, shares, price, total, datetime, userID) VALUES (:symbol, :shares, :price, :total, :datetime, :userID)",
                   symbol=result["symbol"], shares=shares, price=result["price"], total=topay, datetime=datetime.datetime.now(), userID=session["user_id"])
        # flash a message to user
        flash("Successfully bought!")
        return redirect("/")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get("username")
    rows = db.execute("SELECT username FROM users WHERE username = :username", username=username)

    if len(rows) > 0 or len(username) < 1:
        return jsonify(False)
    else:
        return jsonify(True)

    #  Code included inside $( document ).ready() will only run once the page Document Object Model (DOM) is ready for JavaScript code to execute


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    try:
        rows = db.execute("SELECT * FROM purchases WHERE userID= :id ORDER BY datetime", id=session['user_id'])
        return render_template("history.html", rows=rows)

    except:
        return apology("Oh no, something broke")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        # lookup symbol's correspinding price using API, then plug it into quoted template
        # lookup ( request.form ... ) and then p.["price"] should return you the action's price.
        result = lookup(request.form.get("symbol"))
        # in case lookup failed to return desired result, handle this error
        if result == None:
            return apology("Unable to quote", 400)
        return render_template("quoted.html", name=result["name"], symbol=result["symbol"], price=usd(result["price"]))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":

        # validate submitted info, check if username is taken by trying to insert new user into users table
        # request.form.get() returns datatype STRING !
        if not request.form.get("username") or not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Missing username/password!", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match!", 400)

        # generate hash of user's password
        hash = generate_password_hash(request.form.get("password"))
        # insert user's data into users table
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=hash)
        if not result:
            return apology("Username taken!")

        # db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash),
        # {"username": username, "hash": hash})

        # do user a favour, log him in by storing their id in session.get("user_id") ???
        user_id = db.execute("SELECT id FROM users WHERE username = :username", username=request.form.get("username"))
        session['user_id'] = user_id[0]["id"]
        # OR session['user_id'] = (db.execute("SELECT id FROM users WHERE username = :username", username = request.form.get("username")))[0]["id"]
        return redirect("/")
        # e.g. [{id: 1}, {id: 2}, {id: 3}] , OR use session["logged_in"] = True


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        rows = db.execute("SELECT symbol FROM purchases WHERE userID = :id GROUP BY symbol", id=session['user_id'])
        # print (rows)
        return render_template("sell.html", rows=rows)

    elif request.method == "POST":

        # validate user input MUST come first!
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Sorry, what do you want to sell?", 400)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        price = lookup(symbol)["price"]

        # if not enough shares to sell, shares not a postive integer
        rows = db.execute("SELECT symbol, SUM(shares) from purchases WHERE userID= :id and symbol = :symbol GROUP BY symbol",
                          id=session['user_id'], symbol=symbol)
        if shares > rows[0]["SUM(shares)"]:
            return apology("Invalid number of shares", 400)

        # update cash in users, insert new transaction in purchases table
        total = price * shares
        db.execute("UPDATE users SET cash = cash + :total WHERE id = :id", total=total, id=session['user_id'])
        db.execute("INSERT INTO purchases(userID, symbol, shares, price, total, datetime) VALUES(:id, :symbol, :shares, :price, :total, :datetime)",
                   id=session['user_id'], symbol=symbol, shares=-shares, price=price, total=-total, datetime=datetime.datetime.now())
        flash("Sold!")
        return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():

    if request.method == "GET":
        rows = db.execute("SELECT cash FROM users WHERE id= :id", id=session['user_id'])
        cash = rows[0]["cash"]
        return render_template("add.html", cash=cash)

    else:
        if not request.form.get("add"):
            return apology("Please add a valid amount of cash", 400)

        db.execute("UPDATE users SET cash = cash + :add WHERE id= :id", id=session['user_id'], add=float(request.form.get("add")))
        rows = db.execute("SELECT cash FROM users WHERE id= :id", id=session['user_id'])
        cash = rows[0]["cash"]

        return render_template("add.html", cash=usd(cash))


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
