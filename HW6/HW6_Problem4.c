#include <stdio.h>
#include <stdlib.h>

// Main function will print Pascal's Triangle
int main(int argc, char *argv[])
{
    // Declare rows
    int rows = atoi(argv[1]);

    // Allocate memory for the 2D array
    int **pascal = (int **)malloc(rows * sizeof(int *));

    // Check if memory was allocated
    if (pascal == NULL)
    {
        printf("Memory not allocated.");
        return 0;
    }
    printf("\n");
    // Use 2D Array to build Pascal's Triangle
    for (int i = 0; i < rows; i++)
    {
        // Set the spaces
        for (int space = 1; space <= rows - i; space++)
        {
            printf("  ");
        }
        // Alocate memory for the curent row
        pascal[i] = (int *)malloc((i + 1) * sizeof(int));
        // Check if allocating memory failed
        if (pascal[i] == NULL)
        {
            printf("Memory allocation failed\n\n");
            exit(1);
        }

        // Save the values in the 2D array
        for (int j = 0; j <= i; j++)
        {
            // The first and last values of every row is 1
            if (j == 0 || j == i)
            {
                pascal[i][j] = 1;
            }
            // Other values are sum of values just above and left of above
            else
            {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
            // Print the values
            printf("%4d", pascal[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // Free the memory
    for (int i = 0; i < rows; i++)
    {
        free(pascal[i]);
    }
    free(pascal);
}
