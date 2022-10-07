#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Ask user for input of unsigned integer
    printf("Enter an intenger value: ");
    unsigned long int input, largestCont = 0;
    scanf("%lu", &input);

    int count = 0;
    int start, end;
    // Loop through bits
    for (int i = 0; i < 32; i++)
    {
        int tmp = 1 << i;

        // Count the Number of continuous 1s
        if (tmp & input)
        {
            count++;
        }
        else
        {
            // Check if new Count is Greater than Previous Counts if so, replace the old info
            if (count > largestCont)
            {
                largestCont = count;
                start = i - count;
                end = i - 1;
            }
            count = 0;
        }
    }
    // Print out the range and Count
    printf("Largest count of 1s was: %ld\n", largestCont);
    printf("In range %d ~ %d \n", start, end);
    return 0;
}