#include <stdio.h>

int main()
{
    // Ask user for input of string
    printf("Enter a string: ");
    char input[100];
    // Scan in string with spaces
    scanf(" %[^\n]", input);
    int count;
    // Loop through the string until the end of the string
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Skip over space characters
        if (input[i] == ' ')
            continue;
        // Loop though the bits of the character
        for (int j = 0; j < 8; j++)
        {
            // Check if the bit is 0
            if (!(input[i] & (1 << j)))
                count++;
        }
    }
    // Print the total number of 0s
    printf("Total 0 bits counted: %d\n", count);
}