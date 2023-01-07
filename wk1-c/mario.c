#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do{
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    // set loop for the rows of both pyramids (building from top to bottom)
    for (int row = 0 ; row < height ; row++){
        // set loop for columns of first pyramid
        for (int colOne = 0 ; colOne < height; colOne++){
            if (row + colOne >= height - 1){
                printf("#");
            }
            else printf(" ");
        }
        printf("  ");
        // set loop for columns of second pyramid
        for (int colTwo = height - 1; colTwo > -1; colTwo--){
            if (row + colTwo >= height - 1){
                printf("#");
            }
        }
        printf("\n");
    }
}