/*
    Created by: Byron Dowling
    
    Title:      Stack Sorting

    This technique reminds me of the neverending towers of Hanoi UVA problem. It is in no way
    efficient as far as Big O speed is concerned but it is an interesting technique in my opinion
    and I was curious how something like this would compare to some of the others.

    The general premise is you load up a stack with the numbers from the array and then you make
    a temporary stack and a place holder value. You pop the top value from the main stack and 
    place it on the empty stack. Then you pop the next top value from the main stack and evaluate
    if it is greater than the top value of the temp stack. If it greater, then we push this value
    to the temp stack, if the top value of the temp stack is larger, then it needs to be popped and
    placed back on the main stack. This interchanging of elements between stacks will continue until
    the main stack is empty.

    As I mentioned, Big O is probably pretty terrible on this. I figure, there is Big O(n) to load the
    stack with the array values, and absolute best case that all the numbers are already in order, there
    is another cost of Big O(n) to transfer all the values to the temp stack in order. Then there is the
    cost of transferring the values from the temp stack back to the array which is another Big O(n) cost.

    So I believe at the absolute best case scenario, this is an O(n^3) algorithm. I beleive the worst case
    sorting of the stack values would be similar to a O(n^2) algorithm similar to bubble sort. Then factor
    in the cost of O(n) for loading the stack and then loading back to the array is another O(n) cost.

    Therefore I believe this is a Big O(n^4) algorithm.

    A version of this that will print to test can be found here: 
    https://replit.com/@ByronDowling/Stack-Sort#main.cpp
*/

#include <iostream>
#include <stack>

namespace StackSort
{
    using namespace std;

    void stackSort(int arr[], int s, int& c)
    {
        stack<int> MS;
        stack<int> TS;

        // Loading main stack with array values
        for (int i = 0; i < s; i++)
        {
            c++;
            MS.push(arr[i]);
        }

        // Stack Sorting
        while (!MS.empty())
        {
            int current = MS.top();
            MS.pop();
            c++;

            if (TS.empty())
            {
                TS.push(current);
            }

            else
            {
                while (current < TS.top())
                {
                    //cout << "Stack Size is: " << TS.size() << endl;
                    
                    c++;

                    MS.push(TS.top());
                    TS.pop();
                    
                    if (TS.empty())
                    {
                        break;
                    }
                }

                TS.push(current);
            }
        }

        int count = s - 1;
    
        while (!TS.empty())
        {
            // cout << TS.top() << " ";
            c++;
            arr[count] = TS.top();
            TS.pop();
            count--;
        }
    }
}