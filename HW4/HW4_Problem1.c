#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Ask user for input of unsigned integer
    printf("Enter an intenger value: ");
    unsigned long int input;
    scanf("%lu", &input);

    // Ask User for range of Strating and Ending bits
    printf("Enter the starting bit position: ");
    int start;
    scanf("%d", &start);
    printf("Enter the ending bit position: ");
    int end;
    scanf("%d", &end);

    // Check if the starting bit is greater than the ending bit
    if (start > end)
    {
        printf("Error: Starting bit is greater than ending bit\n");
        return 0;
    }

    // Check if the starting bit is greater than 31
    if (start > 31)
    {
        printf("Error: Starting bit is greater than 31\n");
        return 0;
    }

    // Loop to mask the bits
    for (int i = 0; i < 32; i++)
    {
        int tmp;
        // If the bit is outside the range, set the mask bit to 0
        if (i < start || i > end)
        {
            // tmp will hold the bit
            tmp = 1 << i;

            // Check if the bit is 1 if so, set it to 0
            if (tmp & input)
                input = input ^ tmp;
        }
    }

    // Print the new value of the input shifting the bits over to the start position
    printf("In the range %d to %d the value is: %lu \n", start, end, input >> start);

    return 0;
}
