#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

// IF DT_DIR  or DT_REG is not defined, define them
#ifndef DT_DIR
#define DT_DIR 4
#endif

// Linked List of Organized Files
struct file
{
    char *name;
    int size;
    struct file *next;
};
struct file *FileList = NULL;
// Append a file to List by size (ascending)
void appendFile(struct file **head, char *name, int size)
{
    struct file *newFile = malloc(sizeof(struct file));
    struct file *current = *head;
    newFile->name = strcpy(malloc(strlen(name) + 1), name);
    newFile->size = size;
    newFile->next = NULL;
    if (*head == NULL)
    {
        *head = newFile;
        return;
    }
    if (size < current->size)
    {
        newFile->next = current;
        current = newFile;
        *head = current;
        return;
    }
    while (current->next != NULL && current->next->size < size)
    {
        current = current->next;
    }
    newFile->next = current->next;
    current->next = newFile;
}
// Get Size of File
long getFileSize(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // Return -1 if file does not exist or cannot be opened
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}
// Traverse Subdirectories
void traverse(char *path)
{
    // Open Directory
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("Error: Directory %s does not exist.\n", path);
        return;
    }
    // Copy Name of Directory
    char *dirName = malloc(strlen(path) + 1);
    strcpy(dirName, path);

    // Read Directory
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if entry is a directory
        if (entry->d_type == DT_DIR)
        {
            // if .git or .vscode, skip
            if (strcmp(entry->d_name, ".git") == 0 || strcmp(entry->d_name, ".vscode") == 0)
            {
                continue;
            }
            // Check if entry is a subdirectory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                // Create new path
                char *new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
                strcpy(new_path, path);
                strcat(new_path, "/");
                strcat(new_path, entry->d_name);

                // Traverse Subdirectory
                traverse(new_path);

                // Free new path
                free(new_path);
            }
        }
        else
        {
            // PathName
            char *pathName = malloc(strlen(path) + strlen(entry->d_name) + 2);
            strcpy(pathName, path);
            strcat(pathName, "/");
            strcat(pathName, entry->d_name);
            long size = getFileSize(pathName);
            if (size == -1)
            {
                // file does not exist or cannot be opened
                continue;
            }
            // Add file to list
            appendFile(&FileList, pathName, size);
            // Free pathName
            free(pathName);
        }
    }
}
// Function to print list
void printList(struct file *head)
{
    struct file *current = head;
    while (current != NULL)
    {
        printf("%d\t%s\n", current->size, current->name);
        current = current->next;
    }
}

int main(int argc, char const *argv[])
{
    // Check if path is given
    if (argc < 2)
    {
        printf("Error: No path given.\n");
        return 0;
    }
    char *Dir = malloc(strlen(argv[1]) + 1);
    strcpy(Dir, argv[1]);

    traverse(Dir);
    printList(FileList);

    return 0;
}
