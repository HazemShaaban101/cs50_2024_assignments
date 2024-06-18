from cs50 import get_string
import math

# define global variables to be accessed by all functions
letters = 0
words = 0
sentences = 0


def main():
    # get string from user
    string = get_string("input string: ")
    count_fun(string)
    indexing_fun()


# counts all letters, words, and sentences in a paragraph
def count_fun(string):
    global letters
    global words
    global sentences
    
    # for each char in the string
    for i in string:
        # if its an alphabet increase letters count
        if i.isalpha():
            letters += 1
        # if its a space increase words count
        elif i == ' ':
            words += 1
        # if its a comma, a question mark, or an exclamation mark, increase sentences count
        elif i == '.' or i == '!' or i == '?':
            sentences += 1
    words += 1
    
# print output based on calculated index
def print_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 1 and index < 16:
        print(f"Grade {index}")
    elif index >= 16:
        print('Grade 16+')

# calculate index using words, letters, and sentences counted, and then call the print_grade function
def indexing_fun():
    L = letters / words * 100
    S = sentences / words * 100
    
    index = round(round(0.0588 * L, 2) - round(0.296 * S, 2) - 15.8, 0)
    print_grade(index)


main()