#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int main()
{
    // Node Variables
    struct node *head = NULL;
    struct node *current = NULL;
    struct node *temp = NULL;
    // Loop over input
    int input;
    while (scanf("%d", &input) != EOF)
    {
        // Create new node
        current = (struct node *)malloc(sizeof(struct node));
        current->data = input;
        current->next = NULL;
        // Add to List
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
    }
    // Bubble Sort List
    if (head != NULL)
    {
        current = head;
        struct node *next = NULL;
        while (current != NULL)
        {
            next = current->next;
            while (next != NULL)
            {
                if (current->data > next->data)
                {
                    int temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            current = current->next;
        }
    }
    else
    {
        printf("No data entered");
    }

    // Print out Sorted List
    temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}