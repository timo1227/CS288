#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Check that both files exist
    FILE *fp = fopen("numbers.txt", "r");
    if (fp == NULL)
    {
        printf("Error: numbers.txt does not exist.\n");
        return 1;
    }
    fclose(fp);
    fp = fopen("numbers.bin", "r");
    if (fp == NULL)
    {
        printf("Error: numbers.bin does not exist.\n");
        return 1;
    }
    fclose(fp);

    // Scan User Input to obtain index
    printf("Input index: ");
    int index;
    while (scanf("%d", &index) != EOF)
    {
        // Print the number at the index from the txt file and the binary file
        fp = fopen("numbers.txt", "r");
        int num;
        for (int i = 1; i <= index; i++)
        {
            fscanf(fp, "%d", &num);
        }
        printf("Input saved in text file: %d\n", num);
        fclose(fp);
        fp = fopen("numbers.bin", "rb");
        index--;
        fseek(fp, index * sizeof(int), SEEK_SET);
        fread(&num, sizeof(int), 1, fp);
        printf("Input saved in binary file: %d\n", num);
        fclose(fp);
        printf("\nInput index: ");
    }
}
