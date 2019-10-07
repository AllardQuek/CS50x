while True:
    # prompt user for STRING input n
    n = input("Number: ")
    if n.isdigit():
        break

# STEP 1: double every other digit starting w/ 2nd to last, then sum the individual digits of these products
l = len(n)
# print("length =", l)
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
# print("first sum =", firstsum)

# STEP 2: sum every other digit starting w/ the the last
# l + 1 IMPT! If 15-digit, need to reach n[0] hence l-j must reach 0
for j in range(1, l+1, 2):
    secsum += int(n[l-j])
# print("secsum =", secsum)

total = firstsum + secsum
# print("total =", total)

if total % 10 == 0:
    if (l == 15) and (n[:2] == '34' or n[:2] == '37'):
        print("AMEX")
    elif (l == 16) and (n[:2] in ('51', '52', '53', '54', '55')):
        print("MASTERCARD")
    elif (l == 13 or l == 16) and n[0] == '4':
        print("VISA")
    else:
        print("INVALID")