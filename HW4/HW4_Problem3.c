#include <stdio.h>

int main()
{
    // Ask user for string input
    printf("Enter a string: ");
    char input[100];
    scanf("%[^\n]", input);

    // Loop through the string until the end of the string
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Skip over space characters
        if (input[i] == ' ')
            continue;
        // Loop though the bits of the character
        for (int j = 0; j < 4; j++)
        {
            // Check if the bit is 1
            if (input[i] & (1 << j))
                input[i] = input[i] ^ (1 << j);
            else
                input[i] = input[i] | (1 << j);
        }
    }
    // Print the new string
    printf("The new string is: %s\n", input);
    return 0;
}