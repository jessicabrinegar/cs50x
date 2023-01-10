#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Encrypt plaintext given a key, turning it into ciphertext
// Make encrypted message retain the casing and punctuation of the plaintext

bool get_validity(string);
void replace_plaintext(string, string);
int keyLength;

int main(int argc, string argv[])
{
    // Ensure there are two arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Get length of the key
    string key = argv[1];
    keyLength = strlen(key);
    // Ensure the key given by user is valid
    bool keyValidity = get_validity(key);
    // If not, remind them what a valid key is
    if (!keyValidity)
    {
        printf("Key must contain 26 unique alphabetical characters! \n");
        return 1;
    }
    // Get plaintext from user
    string plaintext = get_string("plaintext: ");
    // Return the ciphertext
    printf("ciphertext: ");
    replace_plaintext(plaintext, key);

}

bool get_validity(string argv)
{
    // If key is less or more than 26 characters, it is not valid
    if (keyLength < 26 || keyLength > 26)
    {
        return false;
    }
    // Loop through the key
    for (int i = 0; i < keyLength; i++)
    {
        // If there is a character that is not alphabetical, the key is not valid
        if (!isalpha(argv[i]))
        {
            return false;
        }
        // If there is a diplucate character, the key is not valid
        for (int j = i + 1; j < keyLength; j++)
        {
            if (argv[i] == argv[j])
            {
                return false;
            }
        }
    }
    return true;
}

void replace_plaintext(string plaintext, string key)
{
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int textLength = strlen(plaintext);
    // Loop through the plaintext
    for (int i = 0; i < textLength; i++)
    {
        // If the plaintext character is not a letter, then just print the same character (no replacement)
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        else
        {
            // If it is a letter, then loop through the letters list to find a match
            for (int x = 0; x < 26; x++)
            {
                if (tolower(plaintext[i]) == letters[x])
                {
                    // Print the letter from the key that has the same index as the one from letters list
                    // These conditionals retain casing
                    if (islower(plaintext[i]))
                    {
                        char result = tolower(key[x]);
                        printf("%c", result);
                    }
                    else
                    {
                        char result = toupper(key[x]);
                        printf("%c", result);
                    }
                }
            }
        }
    }
    printf("\n");
}