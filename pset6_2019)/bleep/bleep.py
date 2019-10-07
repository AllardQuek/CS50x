# from cs50 import get_string
# from sys import argv
import sys


def main():
    # Opens and reads from that file the list of words stored therein, one per line, AND stores each in a Python data structure for later access.
    # While a Python list will work well for this, you may also find a set useful here
    # Error if user did not input 2 args ONLY, exit with status code 1
    if len(sys.argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")

    # Step 1: Create and populate set of banned words

    # use curly braces {} or set() to create a list,
    # Note: to create an empty set you have to use set(), not {}; the latter creates an empty dictionary
    banned = set()

    file = open(sys.argv[1], "r")
    for line in file:
        # strip away white space in each line, then add bword to the SET/list
        bword = line.strip()
        banned.add(bword)

    # Step 2: Prompt user for message, split and collect words in a list
    message = input("What message would you like to censor?\n")
    wordslist = message.split()

    # Check for matches of words with banned words, prints back user's message, replacing chars in banned words with a *
    for word in wordslist:
        # if word in message found in banned set of words, case-insensitive so convert message word to lowercase to match that in dictionary.txt
        if word.lower() in banned:
            # print a no. of * equal to the length of the word, THEN a space, THEN don't print newline
            print('*' * len(word), '', end='')
        else:
            # Don't print newline after printing each word
            print(word, '', end='')

    # NOW print newline to shift command prompt down
    print()

    # ALWAYS rmb to close file after opening
    file.close()


if __name__ == "__main__":
    main()
