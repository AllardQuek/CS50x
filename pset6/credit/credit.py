while True:
    # prompt user for STRING input n
    n = input("Number:")
    if n.isdigit():
        break

# STEP 1: double every other digit starting w/ 2nd to last, then sum the individual digits of these products
l = len(n)
if l not in (13, 15, 16):
    print("INVALID")

firstsum = 0
secsum = 0

# I can only index strings NOT integers
# if 13-digit, l//2 + 1 = 7, thus range is 1 to (not including) 7
# if 16-digit, l//2 + 1 = 9, thus range is 1 to (not including) 9, 16-16 = 0
for i in range (1, l//2 + 1):
    number = int(n[l-i*2]) * 2
    if number > 9:
        # 12, 12%10 = 2, 12//10 = 1
        firstsum = firstsum + number%10 + number//10
    else:
        firstsum += number
print(firstsum)

# STEP 2: sum every other digit starting w/ the the last
for j in range(1, l, 2):
    secsum += int(n[l-j])
print(secsum)

total = firstsum + secsum
print(total)

if total % 10 == 0:
    if l == 15:
        if n[:2] == 34 or n[:2] == 37:
            print("AMEX")
    if l == 13 or l == 16:
        if n[0] == 4:
            print("VISA")

else:
    print("INVALID")





#print("AMEX\n or MASTERCARD\n or VISA\n or INVALID\n")