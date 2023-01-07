#include <cs50.h>
#include <stdio.h>

int main(void)
{
// TODO: Prompt for start size
    int startN;
    do{
        startN = get_int("Start size: ");
    }
    while (startN < 9);
    int born = startN / 3;
    int lost = startN /4;

// TODO: Prompt for end size
    int endN;
    do{
        endN = get_int("End size: ");
    }
    while (endN < startN);

// TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (endN > startN){
        startN = startN + (startN / 3) - (startN / 4);
        years++;
    }

// TODO: Print number of years
    printf("Years: %i\n", years);
}
