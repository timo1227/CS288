#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Global array to share between processes
int *arr;

// MPI Count sort function
void *countElems(int *arr, int size, int rank, int world_size)
{
    // Get the number of elements to be sorted by each process
    int numElems = size / world_size;
    // Print Process Rank
    printf("Process %d:\n", rank);
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

    // // Create a displacements array to store the displacements of each unique element
    // int *displs = (int *)malloc(sizeof(int) * 10);

    // // Initialize the displacements array to 0
    // for (int i = 0; i < 10; i++)
    // {
    //     displs[i] = 0;
    // }

    // // Calculate the displacements of each unique element
    // for (int i = 1; i < 10; i++)
    // {
    //     displs[i] = displs[i - 1] + count[i - 1];
    //     printf("displs[%d] = %d \n", i, displs[i]);
    // }

    // Create a temp array to store the sorted elements
    int *temp = (int *)malloc(sizeof(int) * size);

    // Sort the elements in the array
    for (int i = start; i < end; i++)
    {
        // to do
        int val = arr[i];
        printf("val = %d\n", val);
        count[val]++;
    }

    // Copy the sorted elements to the original array
    for (int i = start; i < end; i++)
    {
        arr[i] = temp[i];
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

    // Create Array of Random Ints
    int size = 10;
    arr = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }

    // Print the array before sorting
    if (world_rank == 0)
    {
        printf("Array before sorting:\n");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Call the MPI Count sort function
    countElems(arr, size, world_rank, world_size);
    // Finalize the MPI environment.
    MPI_Finalize();
}

/*
https://www.codingame.com/playgrounds/349/introduction-to-mpi/non-blocking-communications---exercise
https://spagnuolocarmine.github.io/counting-sort.html
*/