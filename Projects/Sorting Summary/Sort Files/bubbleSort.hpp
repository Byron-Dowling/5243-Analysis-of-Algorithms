// Bubblesort in C++
// Code inspiration from:
// https://www.geeksforgeeks.org/bubble-sort/

#include <iostream>

namespace BubbleSort
{
    using namespace std;

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
    
    // A function to implement bubble sort
    void bubbleSort(int arr[], int n, int& c)
    {
        int i, j;

        for (i = 0; i < n-1; i++)
        {
            // Last i elements are already in place
            for (j = 0; j < n-i-1; j++)
            {
                //c++;
                if (arr[j] > arr[j+1])
                {
                    c++;
                    swap(&arr[j], &arr[j+1]);
                }
            }
        }
    }
}