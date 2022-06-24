/*
WRITTEN BY ERIC 7 APRIL 2022

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
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float letter_count = count_letters(text);
    float word_count = count_words(text);
    float sentence_count = count_sentences(text);
    // printf("%i letters\n%i words\n%i sentences\n", letter_count, word_count, sentence_count);
    // calculate Coleman-Liau index
    float L = 100 * letter_count / word_count;
    float S = 100 * sentence_count / word_count;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
// Compute and return letter count
{
    int letter_count = 0;
    int letter_point = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // convert all letters in words to lowercase
        text[i] = tolower(text[i]);
        // first find ASCII dec value of letter
        int letter_ascii = (int) text[i];
        // exclude all non lower-case letters from the counting
        // ASCII array for lowercase letters is 97 (a) - 122 (z)
        // if letter is not lowercase a-z, letter point is set to 0
        if (letter_ascii < 97 || letter_ascii > 122)
        {
            letter_point = 0;
        }
        else
        {
            // add letter points to running score
            letter_count ++;
        }
    }
    return letter_count;
}

int count_words(string text)
// Compute and return word count
{
    int word_count = 0;
    int letter_point = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // find ascii dec value of letter
        int letter_ascii = (int) text[i];
        // if character is a space (ASCII value = 32), then add 1 to word count
        if (letter_ascii == 32)
        {
            word_count ++;
        }
    }
    if (word_count > 0)
    {
        // return word count + 1 because the last word won't have a space after it
        return word_count + 1;
    }
    else
    {
        return 0;
    }
}

int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // find ascii dec value of letter
        int letter_ascii = (int) text[i];
        // if character is one of these end of sentence delimiters: ! = 33, . = 46, ? = 63, add one to sentence total
        if (letter_ascii == 33 || letter_ascii == 46 || letter_ascii == 63)
        {
            sentence_count ++;
        }
    }
    return sentence_count;
}