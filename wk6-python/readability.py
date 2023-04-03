from cs50 import get_string
from re import findall


def main():
    input = get_string("Text: ")
    # Count the # of letters
    letters = len([char for char in input if char.isalpha()])
    # Count the # of words
    words = len(input.split())
    # Count the # of sentences
    sentences = len(findall(r"[?!.]", input))
    readability = calculate_grade(letters, words, sentences)

    if readability <= 0:
        print("Before Grade 1")
    elif readability >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {readability}")


def calculate_grade(letters, words, sentences):
    # Find avg # of letters per 100 words
    avgL = letters / words * 100
    # Find avg # of sentences per 100 words
    avgS = sentences / words * 100
    # Calculate the grade level using the Coleman-Liau index
    grade = round(0.0588 * avgL - 0.296 * avgS - 15.8)
    return grade


main()