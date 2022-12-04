#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Check if numbers.txt exists and is empty
    FILE *fp = fopen("numbers.txt", "r");
    if (fp == NULL)
    {
        // If it doesn't exist, create it
        fp = fopen("numbers.txt", "w");
        fclose(fp);
    }
    else
    {
        // If it does exist, check if it is empty
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            // If it is empty continue
            fclose(fp);
        }
        else
        {
            // If it is not empty, truncate it
            fclose(fp);
            fp = fopen("numbers.txt", "w");
            fclose(fp);
        }
    }

    // Check if numbers.bin exists and is empty
    fp = fopen("numbers.bin", "r");
    if (fp == NULL)
    {
        // If it doesn't exist, create it
        fp = fopen("numbers.bin", "w");
        fclose(fp);
    }
    else
    {
        // If it does exist, check if it is empty
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            // If it is empty continue
            fclose(fp);
        }
        else
        {
            // If it is not empty, truncate it
            fclose(fp);
            fp = fopen("numbers.bin", "w");
            fclose(fp);
        }
    }

    // Scan Integers and save them into a txt file and a binary file
    int num, count = 1;
    printf("Input data %d : ", count);
    while (scanf("%d", &num) != EOF)
    {
        // Save to txt file
        fp = fopen("numbers.txt", "a");
        fprintf(fp, "%d\n", num);
        fclose(fp);
        // Save to binary file
        fp = fopen("numbers.bin", "a");
        fwrite(&num, sizeof(int), 1, fp);
        fclose(fp);
        count++;
        printf("Input data %d : ", count);
    }
    printf("\n");
}
