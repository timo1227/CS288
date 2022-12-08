#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX 1000

int arr[MAX]; // Remove this array create local one in each process
// pass size of array to each process and function so it can sort them with correct ammount of elements
bool containZero = false;

// MPI Count sort function
void *countElems(int *arr, int size, int rank, int world_size, char filename[] = NULL)
{
    MPI_Request request;
    MPI_Status status;

    // Get the number of elements to be sorted by each process
    int numElems = size / world_size;
    // Get the starting index of the array for each process
    int start = rank * numElems;
    // Get the ending index of the array for each process
    int end = start + numElems;
    // Create a count array to store the count of each unique element
    int *count = (int *)malloc(sizeof(int) * size);

    // Initialize the count array to 0
    for (int i = 0; i < size; i++)
    {
        count[i] = 0;
    }

    // Sort the elements in the array
    for (int i = start; i < end; i++)
    {
        int val = arr[i];
        count[val]++;
    }

    if (rank == 0)
    {
        // Send the count array to 1
        MPI_Isend(count, size, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        // Wait for the count from final process
        MPI_Wait(&request, &status);
        // Receive the count array from final process
        int *finalCount = (int *)malloc(sizeof(int) * size);
        MPI_Recv(finalCount, size, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, &status);
        // Sort the array using the count array
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < finalCount[i]; j++)
            {
                arr[index] = i;
                index++;
            }
        }

        // Print the sorted array
        // for (int i = 0; i < size; i++)
        // {
        //     if (i == 0 && containZero)
        //     {
        //         printf("%d ", arr[i]);
        //     }
        //     else if (arr[i] == 0)
        //     {
        //         continue;
        //     }
        //     printf("%d ", arr[i]);
        // }

        // Save the sorted array to the file
        FILE *file = fopen(filename, "wb");
        for (int i = 0; i < size; i++)
        {
            if (i == 0 && containZero && arr[i] == 0)
            {
                fwrite(&arr[i], sizeof(int), 1, file);
            }
            else if (arr[i] == 0)
            {
                continue;
            }
            fwrite(&arr[i], sizeof(int), 1, file);
        }
    }
    else
    {
        // Receive the count array from previous process
        int *prevCount = (int *)malloc(sizeof(int) * size);
        MPI_Recv(prevCount, size, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        // Add the count array to the previous count array
        for (int i = 0; i < size; i++)
        {
            count[i] += prevCount[i];
        }
        // Send the count array to next process
        if (rank != world_size - 1)
        {
            MPI_Isend(count, size, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &request);
        }
        else
        {
            // Send the count array to 0
            MPI_Isend(count, size, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char *fileName;
    int size = 0;
    if (world_rank == 0)
    {
        // Ask User for the file name
        printf("Enter the file name: ");
        scanf("%s", fileName);

        // Open the binary file
        FILE *file = fopen(fileName, "rb");
        while (file == NULL)
        {
            printf("File not found. Enter the file name again: ");
            scanf("%s", fileName);
            file = fopen(fileName, "rb");
        }
        // Save number of ints in the file and get size
        int num;
        while (fread(&num, sizeof(int), 1, file))
        {
            // printf("%d ", num);
            arr[size] = num;
            if (num == 0)
            {
                containZero = true;
            }
            size++;
        }
        printf("\n");
        // Close the file
        fclose(file);
        // Send the array to process 1
        MPI_Send(arr, MAX, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // Call the MPI Count sort function
        countElems(arr, MAX, world_rank, world_size, fileName);
        // Save the sorted array to the file
        printf("END process %d\n", world_rank);
    }
    else
    {
        // Receive the array from previous process
        MPI_Recv(arr, MAX, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Send the array to next process
        if (world_rank != world_size - 1)
        {
            MPI_Send(arr, MAX, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);
        }
        // Call the MPI Count sort function
        countElems(arr, MAX, world_rank, world_size);
    }
    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}

/*
https://www.codingame.com/playgrounds/349/introduction-to-mpi/non-blocking-communications---exercise
https://spagnuolocarmine.github.io/counting-sort.html
*/