#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Main function will examine Environment Variables and Sort them
int main(int argc, char *argv[], char *envp[])
{
    // Use Strtok to remove the = from the Environment Variables
    for (int i = 0; envp[i] != NULL; i++)
    {
        char *token = strtok(envp[i], "=");
    }
    // Sort the Environment Variables
    for (int i = 0; envp[i] != NULL; i++)
    {
        for (int j = i + 1; envp[j] != NULL; j++)
        {
            if (strcmp(envp[i], envp[j]) > 0)
            {
                char *temp = envp[i];
                envp[i] = envp[j];
                envp[j] = temp;
            }
        }
    }
    // Add = back to the Environment Variables
    printf("Sorted Environment Variables\t\n");
    printf("====================================\n");
    for (int i = 0; envp[i] != NULL; i++)
    {
        // get string length of envp[i]
        int length = strlen(envp[i]);
        // at the end of the string, add a newline character
        envp[i][length] = '=';
        // print the string
        printf("\t\t%s\n", envp[i]);
    }
    printf("\n");
    printf("\n");
}