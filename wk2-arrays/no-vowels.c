// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void replace(string);
// argv is an array of strings! not one string
// The first element of argv is found at argv[0], the last element is found at argv[argc-1]
int main(int argc, string argv[])
{
    // There should be two arguments (./no-vowels & string)
    if (argc != 2)
    {
        printf("There must be exactly one argument.\n");
        return 1;
    }
    replace(argv[1]);
    return 0;
}
// a --> 6 , e --> 3 , i --> 1 , o --> 0 , u --> no change
void replace(string argv)
{
    int length = strlen(argv);
    char replacement[length];
    for (int i = 0; i < length; i++)
    {
        switch (argv[i])
        {
            case 'a':
                printf("%c", (char)'6');
                break;
            case 'e':
                printf("%c", (char)'3');
                break;
            case 'i':
                printf("%c", (char)'1');
                break;
            case 'o':
                printf("%c", (char)'0');
                break;
            default:
                printf("%c", (char)argv[i]);
                break;
        }
    }
    printf("\n");
}