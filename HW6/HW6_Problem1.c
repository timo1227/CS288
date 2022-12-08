#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Main function will examine the Parameter passed to it
// and will print out the adress and bytes of the parameter
int main(int argc, char *argv[])
{
    // Check to see if the user passed a parameter
    if (argc < 2)
    {
        printf("Please pass a parameter to the program\n");
        return 1;
    }

    printf("argv \t| ");
    unsigned char *p = (unsigned char *)&argv;
    for (int i = 7; i > -1; i--)
    {
        printf("%02hhx ", p[i]);
    }
    printf("| %p\n", p);
    printf("\n");
    printf("\n");

    // For every parameter passed to the program print out the address and bytes
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] | ", i);
        unsigned char *p = (unsigned char *)&argv[i];
        // Print out the bytes of the parameter
        for (int j = 7; j > -1; j--)
        {
            printf("%02hhx ", p[j]);
        }
        printf("| %p\n", p);
    }
    printf("\n");
    printf("\n");

    // Pointer at argv[0]
    unsigned char *p0 = argv[0];

    // Align the pointer to the closest 8 byte boundary
    unsigned char *p1 = (unsigned char *)((unsigned long long)p0 & ~0x7);

    for (int i = 0; i < argc; i++)
    {
        // Print out the bytes of the parameter
        printf(" \t|");
        for (int j = 7; j >= 0; j--)
        {
            // Check if symbol is printable
            if (isprint(p1[j]))
            {
                printf("%02hhx(%c) ", p1[j], p1[j]);
            }
            else
            {
                printf("%02hhx(\\%d) ", p1[j], p1[j]);
            }
        }
        printf("\t| %p\n", p1);
        // Move to the next 8 byte boundary
        p1 += 8;
    }
    printf("\n");
    printf("\n");

    return 0;
}