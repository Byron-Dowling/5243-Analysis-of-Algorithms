#include <iostream>
#include <vector>

namespace HashTable
{
    using namespace std;

    typedef vector<int> Vint;

    vector<Vint> HT;

    void printTable()
    {
        for (int i = 0; i < HT.size(); i++)
        {
            if (!HT[i].empty())
            {
                for (int j = 0; j < HT[i].size(); j++)
                {
                    cout << HT[i][j] << " ";
                }
            }
        }
    }
    

    void buildTable(int key)
    {
        HT[key].push_back(key);
    }


    void hashTable(int arr[], int s)
    {
        int TableSize = 113;
        HT.resize(TableSize);

        for (int i = 0; i < s; i++)
        {
            buildTable(arr[i]);
        }
    }

}