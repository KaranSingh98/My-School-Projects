/**

@author Karanveer Singh
@date December 11, 2018
@assignment CSCI 235 - Project 5
@file SortingTests.cpp

This is the implemenation file for the functions in SortingTests.hpp

*/

#include "SortingTests.hpp"

/**
 @post Sorts an array in ascending order using the selection sort algorithm.
 @param a the array to sort
 @param size the number of elements in a
 */
void selectionSort(int a[], size_t size)
{
    int min;

    for(int i = 0; i < size; i++)
    {
        min = a[i];

        for(int j = i+1; j < size; j++)
        {
            if(a[j] < min)
                min = a[j];
        }

        std::swap(min, a[i]);
    }
}


/**
 @post Sorts an array in ascending order using insertion sort.
 @param a the array to sort
 @param size of the array
 */
void insertionSort(int a[], size_t size)
{
   int i, key, j;

   for (i = 1; i < size; i++)
   {
       key = a[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && a[j] > key)
       {
           a[j+1] = a[j];
           j = j-1;
       }
       a[j+1] = key;
   }
}


/**
@post merges and sorts two halves from mergeSort
@param the array to sort
@param the first value
@param the middle value
@param the last value
*/
void merge(int a[], int l, int m, int r)
{
    int i, j, k;

    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int* L = new int [n1];
    int* R = new int [n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];

    for (j = 0; j < n2; j++)
        R[j] = a[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }

        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    delete [] L;
    delete [] R;
}


/**
 @post Sorts the elements in a range of a array.
 @param a the array with the elements to sort
 @param from the first position in the range to sort
 @param to the last position in the range to sort (included)
 */
void mergeSort(int a[], int from, int to)
{
    if(from < to)
    {
        int mid = (from + (to - 1)) / 2;

        // split the data into two seperate halves
        mergeSort(a, from, mid);
        mergeSort(a, mid + 1, to);

        // merge and sort the two halves
        merge(a, from, mid, to);
    }
}


/**
 @post Populates values with randomly generated numbers in range size
 @param values the array to populate
 @param size of the array to be populated
 */
void generateRandomArray(int values[], size_t size)
{
    srand(static_cast<unsigned>(time(0)));

    for(int i = 0; i < size; i++)
        values[i] = rand() % size;
}


/**
 @post Populates values with integers in ascending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateAscendingArray(int values[], size_t size)
{
    for(int i = 0; i < size; i++)
        values[i] = i;
}


/**
 @post Populates values with integers in descending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateDescendingArray(int values[], size_t size)
{
    for(int i = size; 0 < i; i--)
        values[i] = i;
}


/**
 @post Populates values with integers in ascending order except for the last 10 that are randomly generated
 @param values the array to populate
 @param size of the array to be populated
 */
void generateLastTenRandomArray(int values[], size_t size)
{
    srand(static_cast<unsigned>(time(0)));

    for(int i = 0; i < size; i++)
    {
        if(i < size - 10)
            values[i] = i;
        else
            values[i] = rand() % size;
    }
}


/**
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */
void generateFewRandomArray(int values[], size_t size)
{
    srand(static_cast<unsigned>(time(0)));

    for(int i  = 0; i < size; i++)
        values[i] = rand() % size / 10;
}


/**
 @post Sorts values in ascending order and averages its runtime over 10 runs
 @param sortingFunction the function used to sort the array
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size)
{
    double runtime_sum = 0;

    for(int i = 0; i < 10; i++)
    {
        int* temp = new int[size];

        for(int j = 0; j < size; j++)
            temp[j] = values[j];

        auto start_time = high_resolution_clock().now();
        sortingFunction(temp, size);
        auto end_time = high_resolution_clock().now();

        duration <float, std::micro> run_time = duration_cast <microseconds> (end_time - start_time);

        runtime_sum += run_time.count();

        delete [] temp;
    }

    return runtime_sum / 10;
}


/**
 @post Sorts values in ascending order using mergeSort and averages its runtime over 10 runs
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double mergeSortTest(int values[], size_t size)
{
    double runtime_sum = 0;

    for(int i = 0; i < 10; i++)
    {
        int* temp = new int [size];

        for(int j = 0; j < size; j++)
            temp[j] = values[j];

        auto start_time = high_resolution_clock().now();
        mergeSort(temp, 0, size - 1);
        auto end_time = high_resolution_clock().now();

        duration <float, std::micro> run_time = duration_cast <microseconds> (end_time - start_time);

        runtime_sum += run_time.count();

        delete [] temp;
    }

    return runtime_sum / 10;
}
