/*
    Created by: Byron Dowling

    Title:      Linear Sorting via a Hash Map.

    Essentially you linearly traverse the array and insert the number into the numerical
    index of the map and incrememnt and int counter. When you print an unordered map, it prints
    in numerical order, therefore we only have to print the map from start to finish and at each
    index check if we need to loop to print multiple times if the count is higher than 1.

    In Big O terms, we only have O(n) to traverse the array and insert into the map, then it is
    a constant time to print the map with a potential cost of Big O(longest chain), so if there
    is an array with 4 duplicate values, it would be Big O(n) * Big O(4) = O(4n) <==> O(n)

    A version of this that will print to test can be found here: 
    https://replit.com/@ByronDowling/Maps#main.cpp
*/

#include<iostream>
#include<map>
#include<sstream>

namespace HashMap
{
    using namespace std;

    map<int, int> HM;

    void buildTable(int key)
    {
        HM[key] += 1;
    }

    void printMap()
    {
        map<int, int>::iterator it;
    
        for(it = HM.begin(); it != HM.end(); it++)
        {
        for (int i = 0; i < it->second; i++)
            {
            cout << it->first << " ";
            }
        }
    }

    void hashMap(int arr[], int s)
    {
        for (int i = 0; i < s; i++)
        {
            buildTable(arr[i]);
        }
    }


}