#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int main()
{
    // Set up Variables
    struct node *head = NULL;
    struct node *current = NULL;
    struct node *temp = NULL;
    // Loop over input
    int input, i = 1;
    printf("Input data for node %d: ", i);
    while (scanf("%d", &input) != EOF)
    {
        // Create new node
        current = (struct node *)malloc(sizeof(struct node));
        current->data = input;
        current->next = NULL;

        // Add to list
        if (head == NULL)
        {
            head = current;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = current;
        }
        // Increment counter
        i++;
        printf("Input data for node %d: ", i);
    }
    // Print out list
    temp = head;
    printf("\nData entered in the list are:\n");
    while (temp != NULL)
    {
        printf("Data = %d\n", temp->data);
        temp = temp->next;
    }
    printf("\n");
    // Reverse list
    struct node *prev = NULL;
    struct node *next = NULL;
    current = head;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    // Print out list
    temp = head;
    printf("The list in reverse: \n");
    while (temp != NULL)
    {
        printf("Data = %d\n", temp->data);
        temp = temp->next;
    }
}