/*
    Created by: Byron Dowling
    Title:      Selection Sort

    Simple straightforward implementation of Selection Sort.
    This code is available on replit here: https://replit.com/@ByronDowling/Maps#main.cpp
    *File implements Selection Sort and a Hash Map
*/

#include<iostream>

namespace SelectionSort
{
    using namespace std;

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void selectionSort(int arr[], int size, int& c)
    {
        for (int i = 0; i < size - 1; i++)
        {
            int min = arr[i];
            int x = i;
            int y;

            c++;

            bool swapped = false;

            for (int j = i+1; j < size; j++)
            {
                int curr = arr[j];

                if (curr < min)
                {
                min = curr;
                y = j;
                swapped = true;
                }

                c++;
            }

            if (swapped)
            {
            swap(&arr[x], &arr[y]);
            }
        }
    }
}