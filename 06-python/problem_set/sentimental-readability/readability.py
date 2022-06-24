'''
WRITTEN BY ERIC 29 APRIL 2022

Spec from CS50X:
Design and implement a program, 'readability', that computes the Coleman-Liau index of text.
Implement your program in a file called readability.c in a directory called readability.
Your program must prompt the user for a string of text using get_string.

Your program should count the number of letters, words, and sentences in the text. You may
assume that a letter is any lowercase character from a to z or any uppercase character from
A to Z, any sequence of characters separated by spaces should count as a word, and that any
occurrence of a period, exclamation point, or question mark indicates the end of a sentence.
Your program should print as output "Grade X" where X is the grade level computed by the
Coleman-Liau formula, rounded to the nearest integer.

If the resulting index number is 16 or higher (equivalent to or greater than a senior
undergraduate reading level), your program should output "Grade 16+" instead of giving the
exact index number. If the index number is less than 1, your program should output "Before
Grade 1".

Coleman-Liau index is computed as:

0.0588 * L - 0.296 * S - 15.8

where L is the average number of letters per 100 words in the text, and S is the average
number of sentences per 100 words in the text.

'''
from cs50 import get_string


def main():
    # get string from user
    text = get_string("Text: ")

    # function testing
    # print(letter_count(text))
    # print(word_count(text))
    # print(sentence_count(text))

    # calculate the Coeman-Liau index
    L = 100 * letter_count(text) / word_count(text)
    S = 100 * sentence_count(text) / word_count(text)
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # print interpreted results of index calculation
    if index < 1:
        print("Before Grade 1")
    elif index > 15:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def letter_count(text):
    # count letters
    # remove all spaces from text
    text = text.replace(" ", "")
    l = 0
    # count all alphabetical characters in text
    for letter in text:
        if letter.isalpha():
            l += 1
    return(l)


def word_count(text):
    # count words
    # split text into a list of all words (splits at whitespace by default)
    text = text.split()
    return(len(text))


def sentence_count(text):
    # count sentences
    s = 0
    # loop through all characters and count whenever an end of sentence
    # punctuation is found
    for char in text:
        if (char == "." or char == "!" or char == "?"):
            s += 1
    return(s)


if __name__ == "__main__":
    main()