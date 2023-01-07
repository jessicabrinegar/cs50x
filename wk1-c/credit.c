#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/* 4003600000000014 // --> count = 16 , i = 15 */


int get_length(long);
int multiply_and_sum(long);
int sum_every_other_digit(long);
int sum_remaining_digits(long);
bool is_card_valid(long);
bool is_amex_valid(long, int); //15 digits, starts with 34 or 37
bool is_visa_valid(long, int); // 13 & 16 digit #s and starts with a 4
bool is_mc_valid(long, int); // 16-digit numbers, 51, 52,53,54,55
void get_card_type(long, int);

int main(void)
{
    long creditNum = get_long("Number: ");
    // Get the number of digits of the credit card number
    int numDigits = get_length(creditNum);
    // Ensure credit number is valid
    bool valid = is_card_valid(creditNum);
    if (valid)
    {
        get_card_type(creditNum, numDigits);
    }
    else
    {
        printf("INVALID\n");
    }

}
int get_length(long creditNum)
{
    int count = 0;
    // Integer division gets rid of the decimal point
    while (creditNum != 0)
    {
        // Add 1 count until you have a decimal (you have cycled through all numbers)
        creditNum /= 10;
        count += 1;
    }
    return count;
};
void get_card_type(long creditNum, int numDigits)
{
    if (is_mc_valid(creditNum, numDigits))
    {
        printf("%s", "MASTERCARD\n");
    }
    else if (is_amex_valid(creditNum, numDigits))
    {
        printf("%s", "AMEX\n");
    }
    else if (is_visa_valid(creditNum, numDigits))
    {
        printf("%s", "VISA\n");
    }
    else
    {
        printf("%s", "INVALID\n");
    }
}
bool is_amex_valid(long creditNum, int numDigits)
{
    int firstTwoDigits = (int)(creditNum / pow(10, 13));
    if (numDigits == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//51, 52, 53, 54, or 55
bool is_mc_valid(long creditNum, int numDigits)
{
    int firstTwoDigits = (int)(creditNum / pow(10, 14));
    if (numDigits == 16 && (firstTwoDigits > 50 && firstTwoDigits < 56))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool is_visa_valid(long creditNum, int numDigits)
{
    if (numDigits == 13)
    {
        // Returns the bool value of this expression
        return ((int)(creditNum / pow(10, 12)) == 4);
    }
    else if (numDigits == 16)
    {
        return ((int)(creditNum / pow(10, 15)) == 4);
    }
    else
    {
        return false;
    }
}
int multiply_and_sum(long creditNum)
{
    int sumOfDigits = 0;
    int digitMultiplied = 2 * (creditNum % 10);
    while (digitMultiplied != 0)
    {
        sumOfDigits += digitMultiplied % 10;
        digitMultiplied /= 10;
    }
    return sumOfDigits;
}
int sum_every_other_digit(long creditNum)
{
    // Describes if the current digit should be used, or if it should be skipped
    bool useCurrentDigit = false;
    // Keep track of the summation
    int sum = 0;
    while (creditNum > 0)
    {
        // If useCurrentDigit is true
        if (useCurrentDigit)
        {
            // Add the digit (or sum of digits) to the sum
            sum += multiply_and_sum(creditNum);
        }
        // Switch the bool value of the useCurrentDigit variable
        useCurrentDigit = !useCurrentDigit;
        // Divide creditNum by 10 (removing the last digit)
        creditNum /= 10;
    }
    return sum;
}
int sum_remaining_digits(long creditNum)
{
    // Flip it to where it starts with the last digit instead of the second-to-last one
    bool useCurrentDigit = true;
    int sum = 0;
    while (creditNum > 0)
    {
        if (useCurrentDigit)
        {
            // Returns the digit and adds it to the sum
            sum += creditNum % 10;
        }
        // Switch the bool value of the useCurrentDigit variable
        useCurrentDigit = !useCurrentDigit;
        creditNum /= 10;
    }
    return sum;
}
bool is_card_valid(long creditNum)
{
    // Sum that were multiplied
    int sumOne = sum_every_other_digit(creditNum);
    // Sum that weren't multiplied
    int sumTwo = sum_remaining_digits(creditNum);
    int totalSum = sumOne + sumTwo;
    return ((totalSum % 10) == 0);
}