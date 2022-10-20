#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Get count of numbers to be sorted
    int count;
    // printf("How many numbers do you want to sort? "); // Comment out entier line for bash diff testing
    scanf("%d", &count);

    // Get numbers to be sorted
    int numbers[100];
    // printf("Enter %d numbers to be sorted:\n", count); // Comment out entier line for bash diff testing
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &numbers[i]);
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
            if ((numbers[j] & mask) == 0)
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
            if ((numbers[j] & mask) == 0)
            {
                temp[zeroIndex] = numbers[j];
                zeroIndex++;
            }
            // Otherwise, place in tmp array at after zeroIndex
            else
            {
                temp[oneIndex] = numbers[j];
                oneIndex++;
            }
        }
        // Copy tmp array to numbers array
        for (int j = 0; j < count; j++)
        {
            numbers[j] = temp[j];
        }
    }

    // Print sorted numbers
    for (int i = 0; i < count; i++)
    {
        printf("%d\n", numbers[i]);
    }
}