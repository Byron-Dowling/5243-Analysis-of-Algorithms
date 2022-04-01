// Heap Sort in C++
// Via Dr. Griffin's Programming Techniques Class

#include <iostream>

namespace HeapSort 
{
    using namespace std;

    void heapify(int arr[], int n, int i, int& c) 
    {
        // Find largest among root, left child and right child
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        // Swap and continue heapifying if root is not largest
        if (largest != i)
        {
            c++;
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, c);
        }
    }

    // main function to do heap sort
    void heapSort(int arr[], int n, int& c) {
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i, c);

        // Heap sort
        for (int i = n - 1; i >= 0; i--) 
        {
            c++;
            swap(arr[0], arr[i]);

            // Heapify root element to get highest element at root again
            heapify(arr, i, 0, c);
        }
    }
}