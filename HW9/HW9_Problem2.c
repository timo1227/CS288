#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

// IF DT_DIR  or DT_REG is not defined, define them
#ifndef DT_DIR
#define DT_DIR 4
#endif
#ifndef DT_REG
#define DT_REG 8
#endif

// Linked List of Organized Files
struct file
{
    char *name;
    int size;
    struct file *next;
};
// Linked List of Unscanned Directories
struct dir
{
    char *name;
    struct dir *next;
};
struct file *FileList = NULL;
struct dir *DirList = NULL;
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
// Append a directory to List
void appendDir(struct dir **head, char *name)
{
    struct dir *newDir = malloc(sizeof(struct dir));
    struct dir *current = *head;
    newDir->name = strcpy(malloc(strlen(name) + 1), name);
    newDir->next = NULL;
    if (*head == NULL)
    {
        *head = newDir;
        return;
    }
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newDir;
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
        // Skip Current and Parent Directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        if (entry->d_type == DT_DIR) // If Directory, Append to List
        {
            char *dirPath = malloc(strlen(dirName) + strlen(entry->d_name) + 2);
            strcpy(dirPath, dirName);
            strcat(dirPath, "/");
            strcat(dirPath, entry->d_name);
            appendDir(&DirList, dirPath);
        }
        else if (entry->d_type == DT_REG) // If File, Append to List
        {
            // Get Full Path of File
            char *filePath = malloc(strlen(path) + strlen(entry->d_name) + 2);
            strcpy(filePath, path);
            strcat(filePath, "/");
            strcat(filePath, entry->d_name);
            // Get Size of File
            long size = getFileSize(filePath);
            if (size == -1)
            {
                continue; // Skip File if it does not exist or cannot be opened
            }
            else
            {
                // Append File to List
                appendFile(&FileList, filePath, size);
            }
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

    // Fill DirList with subdirectories
    traverse(Dir);

    // Traverse DirList
    while (DirList != NULL)
    {
        traverse(DirList->name);
        // Remove first element of DirList
        struct dir *temp = DirList;
        DirList = DirList->next;
        free(temp);
    }
    // Print FileList
    printList(FileList);
    return 0;
}
