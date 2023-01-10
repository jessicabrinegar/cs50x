#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Calculate the reading grade level of a text input based on the Coleman-Liau index

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);
int calculate_grade(int letters, int words, int sentences);
// Make the string length variable global so it can easily be used in all the functions
int length;

int main(void)
{
    // Get text input from the user
    string input = get_string("Text: ");
    // Calculate the length of the text input
    length = strlen(input);
    // Count the # of letters
    int letters = count_letters(input);
    // Count the # of words
    int words = count_words(input);
    // Count the # of sentences
    int sentences = count_sentences(input);
    int readability = calculate_grade(letters, words, sentences);

    if (readability <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (readability >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readability);
    }
}

int count_letters(string input)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(input[i]))
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string input)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isspace(input[i]))
        {
            count += 1;
        }
    }
    // Need to add 1 for the last word, as it is not followed by a space
    return count + 1;
}

int count_sentences(string input)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            count += 1;
        }
    }
    return count;
}

int calculate_grade(int letters, int words, int sentences)
{
    // Find avg # of letters per 100 words
    float avgL = (float)letters / (float)words * 100;
    // Find avg # of sentences per 100 words
    float avgS = (float)sentences / (float)words * 100;
    // Calculate the grade level using the Coleman-Liau index
    int grade = round(0.0588 * avgL - 0.296 * avgS - 15.8);
    return grade;
}