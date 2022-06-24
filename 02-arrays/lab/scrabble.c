#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner - CODED BY ERIC 7 APRIL 2022
    if (score1 > score2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Compute and return score for string - CODED BY ERIC 7 APRIL 2022
    int score = 0;
    int letter_points = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // convert all letters in words to lowercase
        word[i] = tolower(word[i]);
        // find scrabble value of letter
        // first find ASCII value of letter
        int letter_ascii = (int) word[i];
        // exclude all non lower-case letters from the counting
        // ASCII array for lowercase letters is 97 (a) - 122 (z)
        if (letter_ascii < 97 || letter_ascii > 122)
        {
            letter_points = 0;
        }
        else
        {
            // 'decode' the letter to get scrabble score 'POINTS' array index
            int decoder = letter_ascii - 97;
            letter_points = POINTS[decoder];
        }
        // add letter points to running score
        score += letter_points;
    }
    return score;
}
