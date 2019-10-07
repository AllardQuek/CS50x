from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    # Take in string inputs, a and b
    # Split each string into lines (https://docs.python.org/3/library/stdtypes.html#string-methods, str.split(sep=None, maxsplit=-1), str.splitlines([keepends]))
    list_a = a.split('\n')
    list_b = b.split('\n')
    set_a = set(list_a)
    set_b = set(list_b)
    # Compute a LIST of all lines which appear in both a and b (data structs to consider: list, set, ... https://docs.python.org/3/tutorial/datastructures.html)
    # list can contain duplicate values but a set CANNOT
    common_lines = list(set_a & set_b)  # gives a set of common lines converted to a list
    # Return the list with NO duplicates
    return common_lines


def sentences(a, b):
    """Return sentences in both a and b"""
    # import sent_tokenize, which returns a list of the sentences in the input string
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)
    set_a = set(list_a)
    set_b = set(list_b)
    common_sentences = list(set_a & set_b)
    return common_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    list_a = []
    list_b = []

    for i in range(0, len(a) - n + 1):  # remember +1 because 2nd paremeter is NOT inclusive
        list_a.append(a[i:i+n])
    for i in range(0, len(b) - n + 1):
        list_b.append(b[i:i+n])

    set_a = set(list_a)
    set_b = set(list_b)
    common_substrings = list(set_a & set_b)

    return common_substrings
