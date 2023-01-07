#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

// Find either sum or average of amount of hours spent per week on coding

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    // Total up hours saved in the array into a new variable
    float sum = 0;
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }
    // Depending on output, return either sum, or the avg # of hrs
    if (output == 'A')
    {
        return sum / weeks;
    }
    else
    {
        return sum;
    }
}