import sys

# get key
key = sys.argv[1]
if len(sys.argv) != 2:
    sys.exit("Usage: python vigenere.py k")

if key.isalpha() == False:
    #print("Usage: python vigenere.py k")
    #exit() ; exit(code=None)
    sys.exit("Usage: python vigenere.py k")  # USE THIS METHOD OF EXITING NOT THE ABOVE!
# get plaintext
p = input("plaintext: ")

# print ciphertext char by char
print("ciphertext: ", end="")

# encipher ci = (pi + kj) % 26, ord(c) converts char to int ; chr(i) converts integer to char
# initialise counter to keep track of position in key
i = 0
# iterate over each char in ptext
for char in p:

    # convert char in key to lowercase, allow for wrapping around key (i % len(key))
    k = ord((key[i % len(key)]).lower()) - 97

    if char.islower():
        cc_int = (ord(char) + k - 97) % 26
        cc = chr(cc_int + 97)
        i += 1
        print(cc, end="")
    elif char.isupper():
        cc_int = (ord(char) + k - 65) % 26
        cc = chr(cc_int + 65)
        i += 1
        print(cc, end="")

    else:
        print(char, end="")
print()
