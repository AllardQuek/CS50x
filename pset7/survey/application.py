import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")
    # no index.html, so redirect to url with /form which gives form.html


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


# when form submitted, POST info if valid, else return error template
@app.route("/form", methods=["POST"])
def post_form():
    # validate: if at least 1 field empty, return error.html
    name = request.form.get("firstname")
    interest = request.form.get("interest")
    gender = request.form.get("gender")
    if not name or not interest or not gender:
        return render_template("error.html", message="Please fill in all fields!")

    # else: - WRITE the form’s values to a new row in survey.csv using csv.writer/csv.DictWriter
    file = open("survey.csv", "a")
    writer = csv.DictWriter(file, fieldnames=['name', 'interest', 'gender'])
    writer.writerow({'name': name, 'interest': interest, 'gender': gender})  # writerow only takes ONE arg
    file.close()

    # REDIRECT user to /sheet.
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # READ past submissions from survey.csv using csv.reader/csv.DictReader and

    with open("survey.csv", "r") as file:
        reader = csv.DictReader(file, fieldnames=['name', 'interest', 'gender'])
        infolist = list(reader)
        return render_template("sheet.html", infolist=infolist)  # i.e name = row[name]

    # display those submissions in an HTML TABLE via a NEW template (sheets.html), style table with Bootstrap
    # Optionally enhance the table with JavaScript, as via DataTables.
    if not request.form.get("firstname") or not request.form.get("interest") or not request.form.get("gender"):
        return render_template("error.html", message="Please fill in all fields!")