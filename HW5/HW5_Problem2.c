#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Get count of numbers to be sorted
    int count;
    // printf("How many numbers do you want to sort? "); // Comment out entier line for bash diff testing
    scanf("%d", &count);
    float f[100];
    // Typecast to float using pointer
    unsigned int *FtoInt = (unsigned int *)&f;
    // Get Float numbers
    for (int i = 0; i < count; i++)
    {
        // printf("\tEnter a float number: "); // Comment out entier line for bash diff testing
        scanf("%f", &f[i]);
    }

    // Radix sort unsigned integers
    for (int i = 0; i < 32; i++)
    {
        // Count number of 0s and 1s
        int mask = 1 << i;
        int zeroCount = 0;
        // Count number of zeros to determine where to place 0s
        // and 1s in the sorted array
        for (int j = 0; j < count; j++)
        {
            if ((FtoInt[j] & mask) == 0)
            {
                zeroCount++;
            }
        }
        // Set tmp array to hold sorted numbers
        int temp[count];
        int zeroIndex = 0;
        int oneIndex = zeroCount;
        for (int j = 0; j < count; j++)
        {
            // If bit is 0, place in tmp array at zeroIndex
            if ((FtoInt[j] & mask) == 0)
            {
                temp[zeroIndex] = FtoInt[j];
                zeroIndex++;
            }
            // Otherwise, place in tmp array at after zeroIndex
            else
            {
                temp[oneIndex] = FtoInt[j];
                oneIndex++;
            }
        }
        // Copy tmp array to numbers array
        for (int j = 0; j < count; j++)
        {
            FtoInt[j] = temp[j];
        }
    }
    // Resort the numbers to move the negative numbers to the front in descending order
    int tmp[count];
    int tmpIndex = 0;
    for (int i = count - 1; i > -1; i--)
    {
        // If number is negative, place in tmp array
        if (f[i] < 0)
        {
            tmp[tmpIndex] = FtoInt[i];
            tmpIndex++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        // If number is positive, place in tmp array
        if (f[i] >= 0)
        {
            tmp[tmpIndex] = FtoInt[i];
            tmpIndex++;
        }
    }
    // Copy tmp array to numbers array
    for (int i = 0; i < count; i++)
    {
        FtoInt[i] = tmp[i];
    }

    // Print sorted Float numbers
    // printf("Sorted Array of Floats: "); // Comment out entier line for bash diff testing
    for (int i = 0; i < count; i++)
    {
        printf("%f", f[i]);
        // printf(" "); // Comment out entier line for bash diff testing
        printf("\n"); // Uncomment out entier line for bash diff testing
    }
    // printf("\n"); // Comment out entier line for bash diff testing
}