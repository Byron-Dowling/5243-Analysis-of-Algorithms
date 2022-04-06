/*
    Name:       Byron Dowling
    Course:     5243 Algorithm Analysis
    Date:       2/10/2022

    Assignment: Sorting Experiments

        Original Assignment Instructions:

        Implement 3 different sorting algorithms on arrays of size 5000. You may choose the sorting
        algorithms, but select one sort from each runtime category: O(n2), O(n log n), O(n). You do not
        need to write the sort code from scratch, however, you should reference where you obtained the
        code if you copy/paste or type exact code from another source.

            - Implement a separate counter for each sort. Initialize the counter to zero and increment
              inside loops of the associated sort. For example, in the O(n2) loop, increment the counter
              inside the inner loop. For recursive sorts, use a global counter; other sorts should either pass
              back the count using a return statement or use a reference variable for the count.

            - Use a system clock timer to start the time immediately before each sort and end immediately
              after each sort. If you don’t know how to do this, Google is your friend. If you still have
              trouble with implementation, see me.

            - Once you have the code working for one run, average the time and counter results over 20
              runs, using a different random seed for each run. An easy way to do this is to use the loop
              control variable as the random seed, rather than time(NULL). Make sure that the arrays
              hold identical values before sorting

        Sort Used:

            - Hash Table        O(n)
            - Radix Sort        O(n)
            - Hash Map          O(n)
            - Heap Sort         O(n log n)
            - Quicksort         O(n log n)
            - Selection sort    O(n^2)
            - Bubble Sort       O(n^2)
            - Stack Sort        O(n^4)
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <sstream>
#include "heapSort.hpp"
#include "radixSort.hpp"
#include "bubbleSort.hpp"
#include "quickSort.hpp"
#include "hashMap.hpp"
#include "hashTable.hpp"
#include "selectionSort.hpp"
#include "stackSort.hpp"


using namespace std;
using namespace std::chrono;


typedef vector<float> Vfloat;       // typedef for a vector of float vectors
typedef vector<int> Vint;           // typedef for a vector of int vectors


/*
 
  $$$$$$\                       $$\               
 $$  __$$\                      $$ |              
 $$ /  \__| $$$$$$\   $$$$$$\ $$$$$$\    $$$$$$$\ 
 \$$$$$$\  $$  __$$\ $$  __$$\\_$$  _|  $$  _____|
  \____$$\ $$ /  $$ |$$ |  \__| $$ |    \$$$$$$\  
 $$\   $$ |$$ |  $$ |$$ |       $$ |$$\  \____$$\ 
 \$$$$$$  |\$$$$$$  |$$ |       \$$$$  |$$$$$$$  |
  \______/  \______/ \__|        \____/ \_______/ 

                                                  
    Description:
		This class is responsible for instantiating an instance of the sort experiment. When an object
        of this class is created, it will initialize an integer array with random numbers and make a 
        copy of this array and send it to the different sorts to be executed and timed as well as
        keeping track of the total number of computations that occur during these sorts. 

        The sorts are all conducted using namespaces that are included from various .hpp files. This
        assignment is somewhat similar to one we did in programming techniques and Dr. Griffin gave us
        some starter code using this namespaced sorting technique so I can't take all the credit for the
        layout. However I have added a significant amount of additional features and sorts to make sure I
        wasn't simply resubmitting a project we already did. In total I have implemented 8 sorts, 
        2 n-squared sorts, 2 n-log-n sorts, 2 linear sorts, and one "bad" sort method that though terrible 
        in Big O terms was fairly interesting, and somewhat tricky to get right.


	Public Methods:
		- Sorts() - Default Constructor
		- Sorts(int S) - Overloaded Constructer
		- vector<float> getTimes() - Returns a vector of run times
		- vector<string> getSorts() - Returns a vector of sort names
		- vector<int> getComps() - Returns a vector of computations
		- void loadData() - Initializes the array of numbers to be sorted with random numbers
		- void printData() - Utility function
		- void copyArray() - Makes a copy of the array that is sent to all the sort functions
		- void runExperiment() - Method that sends the copy array to all the sorts

	Usage:
		- This class creates an object that will run an instance of the sort experiment                                       
 
*/

class Sorts
{
    protected:

        int* data;
        int* copy;
        int size;
        int computations;
        vector<string> sortMethods;
        vector<float> sortTimes;
        vector<int> comps;

    
    public:

        friend class SortExperiment;

        /*
            Default Constructor
        */
        Sorts()
        {
            sortMethods = {"heapSort", "quickSort", "radixSort", "hashMap", "hashTable", "bubbleSort", "selectionSort", "stackSort"};
            size = 20;
            computations = 0;
            data = new int[size];
            copy = new int[size];
        }

        /*
            Overloaded Constructor

            Initializes the sort methods to include all 8 sorts mentioned above.

            Accepts an int to initialize the size that the arrays will be and then we use that
            size to dynamically allocate memory to the main array and the copy array.

            Computations are also initialized to zero.
        */
        Sorts(int S)
        {
            sortMethods = {"heapSort", "quickSort", "radixSort", "hashMap", "hashTable", "bubbleSort", "selectionSort", "stackSort"};
            size = S;
            computations = 0;
            data = new int[S];
            copy = new int[S];
        }


        /*
            Public Method vector<float>: getTimes()

            Description:
                Method that is mainly used by the driver class that is a friend
                class to this one. Is a getter method to retrieve this vector
                of run times for each experiement.

            Params:
                - Accesses member variable vector<float> sortTimes

            Returns:
                - vector<float> sortTimes
        */

        vector<float> getTimes()
        {
            return sortTimes;
        }


        /*
            Public Method vector<string>: getSorts()

            Description:
                Method that is mainly used by the driver class that is a friend
                class to this one. Is a getter method to retrieve this vector
                of sort names that are used when writing results to a file.

            Params:
                - Accesses member variable vector<string> sortMethods

            Returns:
                - vector<string> sortMethods
        */

        vector<string> getSorts()
        {
            return sortMethods;
        }


        /*
            Public Method vector<int>: getComps()

            Description:
                Method that is mainly used by the driver class that is a friend
                class to this one. Is a getter method to retrieve this vector
                of computations

            Params:
                - Accesses member variable vector<int> comps

            Returns:
                - vector<int> comps
        */

        vector<int> getComps()
        {
            return comps;
        }


        /*
            Public Method void: loadData()

            Description:
                Method that will laod the array with random numbers
                between 0 and 100. This method will keep the same numbers
                for each sort, however when a new Sorts object is created
                this will generate new random numbers for the new experiment.

            Params:
                - Accesses member variables data and copy

            Returns:
                - None
        */

        void loadData()
        {
            for (int i = 0; i < size; i++)
            {
                int x = rand();
                x = x % 100;
                data[i] = x;
                copy[i] = x;
            }
        }


        /*
            Public Method void: printData()

            Description:
                Utility method to print the array. Was used during inception
                but not during program runtime.

            Params:
                - prints array that is passed in

            Returns:
                - None
        */

        void printData(int array[])
        {
            for (int i = 0; i < size; i++)
            {
                cout << setw(4) << array[i];
            }

            cout << "\n";
        }


        /*
            Public Method void: copyArray()

            Description:
                Method that initializes the copy array to the contents of the
                main array after the random numbers are generated. In addition to
                doing this initially, it is called after each sort to ensure that each
                sort method is being tested with the same parameters as all of the
                others.

            Params:
                - Accesses member variables data and copy

            Returns:
                - None
        */

        void copyArray() 
        {
            copy = new int[size];

            for (int i = 0; i < size; i++) 
                copy[i] = data[i];
            
        }


        /*
            Public Method void: runExperiment()

            Description:
                Method that is main driver of the sorting experiment itself. The
                method will loop through the list of sortnames and call each sort
                and perform said sort and time how long it takes for each to perform.
                Additionally, a computation counter is passed to keep track of how
                many computations it takes for each sort to complete. The results are
                logged in vectors that are eventually retrieved by the main driver
                class.

            Params:
                - Accesses member variables

            Returns:
                - None
        */

        void runExperiment()
        {
            for (int i = 0; i < sortMethods.size(); i++)
            {
                copyArray();

                cout << "Performing " << sortMethods[i] << "..." << endl;

                auto start = high_resolution_clock::now();

                if (sortMethods[i] == "heapSort")
                {
                    HeapSort::heapSort(copy, size, computations);
                } 
                
                else if (sortMethods[i] == "radixSort") 
                {
                    RadixSort::radixsort(copy, size, computations);
                } 
                
                else if (sortMethods[i] == "bubbleSort") 
                {
                    BubbleSort::bubbleSort(copy, size, computations);
                }

                else if (sortMethods[i] == "quickSort") 
                {
                    QuickSort::quickSort(copy, 0, size - 1, computations);
                }

                else if (sortMethods[i] == "hashMap")
                {
                    HashMap::hashMap(copy, size);
                    computations = size;
                }

                else if (sortMethods[i] == "hashTable")
                {
                    HashTable::hashTable(copy, size);
                    computations = size;
                }

                else if (sortMethods[i] == "selectionSort")
                {
                    SelectionSort::selectionSort(copy, size, computations);
                }

                else if (sortMethods[i] == "stackSort")
                {
                    StackSort::stackSort(copy, size, computations);
                }

                auto stop = high_resolution_clock::now();
                auto duration = duration_cast< microseconds >(stop - start);

                sortTimes.push_back(duration.count());
                comps.push_back(computations);

                cout << "Duration: " << duration.count() << " microSeconds."<< endl;
                cout << "Number of Computations: " << computations << endl << endl;

                delete[] copy;
                computations = 0;
            }
        }


        /*
            User-Defined Destructor to avoid memory leaks

            Since Dynamic Memory is used in two places, the copy array is managed within the
            bulk of the code. However, the main data array needs to have it's dynamic memory
            cleaned up as well during the life of the program. 

            When the object is destroyed, the destructor will run and this will ensure we are
            returning the memory that was allocated in this object.
        */

        ~Sorts()
        {
            delete[] data;
        }
};



/*
 
  $$$$$$\                       $$\                                                               
 $$  __$$\                      $$ |                                                              
 $$ /  \__| $$$$$$\   $$$$$$\ $$$$$$\                                                             
 \$$$$$$\  $$  __$$\ $$  __$$\\_$$  _|                                                            
  \____$$\ $$ /  $$ |$$ |  \__| $$ |                                                              
 $$\   $$ |$$ |  $$ |$$ |       $$ |$$\                                                           
 \$$$$$$  |\$$$$$$  |$$ |       \$$$$  |                                                          
  \______/  \______/ \__|        \____/                                                           
                                                                                                  
                                                                                                  
                                                                                                  
 $$$$$$$$\                                         $$\                                    $$\     
 $$  _____|                                        \__|                                   $$ |    
 $$ |      $$\   $$\  $$$$$$\   $$$$$$\   $$$$$$\  $$\ $$$$$$\$$$$\   $$$$$$\  $$$$$$$\ $$$$$$\   
 $$$$$\    \$$\ $$  |$$  __$$\ $$  __$$\ $$  __$$\ $$ |$$  _$$  _$$\ $$  __$$\ $$  __$$\\_$$  _|  
 $$  __|    \$$$$  / $$ /  $$ |$$$$$$$$ |$$ |  \__|$$ |$$ / $$ / $$ |$$$$$$$$ |$$ |  $$ | $$ |    
 $$ |       $$  $$<  $$ |  $$ |$$   ____|$$ |      $$ |$$ | $$ | $$ |$$   ____|$$ |  $$ | $$ |$$\ 
 $$$$$$$$\ $$  /\$$\ $$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ | $$ | $$ |\$$$$$$$\ $$ |  $$ | \$$$$  |
 \________|\__/  \__|$$  ____/  \_______|\__|      \__|\__| \__| \__| \_______|\__|  \__|  \____/ 
                     $$ |                                                                         
                     $$ |                                                                         
                     \__|                                                                         
 
    Description:
		This class is the main driver of the program. The class will either take a default int
        or have an integer passed in at object declaration that will serve as how many "runs"
        we will conduct on the Sorting Experiment. This will then start a loop up to this number
        and at each iteration, a new Sorts object is created to conduct an instance of the
        experiment. Once that object's experiment is complete, the results are written, then the
        object is destroyed and a new one is created when the loop increments.

        In order to get easier access to some of the data that is calaculated in the other class,
        these classes make use of the friend operator that allows them to have access to and call
        their public methods. 

        Once the runs are complete, the results are printed and written to an outfile.


	Public Methods:
		- SortExperiment() - Default Constructor
		- SortExperiment(int num) - Overloaded Constructer
		- void showExperimentResults(const char* h) - Print results and writes to file
		- void calculateAvgs() - Calculates the runtime and computation averages for each sort
		- void startExperiment() - Starts the process of running the experiment multiple times

	Usage:
		- This class creates an object that will coordinate running the sort experiment several times
*/

class SortExperiment
{
    protected:

        int runs;
        vector<Vfloat> averages;
        vector<Vint> comps;
        vector<float> results;
        vector<int> Avg_Comps;
        vector<string> Names;
        ofstream outfile;
    

    public:

        friend class Sorts;     // Ensures we have access to the methods of the class Sorts

        // Default Constructor
        SortExperiment()
        {
            runs = 5;
            outfile.open("sortingresults.txt");
        }

        /*
            Overloaded constructor that sets the outfile destination and then
            accepts an integer number to determine how many times we want to 
            run the sorting experiement to compute our averages.
        */

        SortExperiment(int num)
        {
            runs = num;
            outfile.open("sortingresults.txt");
        }

        
        /*
            Public Method void: showExperimentResults(const char* h)

            Description:
                Utility method that prints the results to the terminal and also
                writes said results to an outfile destination.

            Params:
                - Accesses member variables

            Returns:
                - None
        */

        void showExperimentResults(const char* h)
        {
            cout << "The results of the experiment are:\n";
            outfile << h << "\n\n";
            outfile << "The results of the experiment are:\n\n";

            for (int i = 0; i < Names.size(); i++)
            {
                cout << "The average time for " << Names[i] << " was " << results[i] << " microseconds.\n";
                cout << "The average number of computations was " << Avg_Comps[i] << "\n\n";
                outfile << "The average time for " << Names[i] << " was " << results[i] << " microseconds.\n";
                outfile << "The average number of computations was " << Avg_Comps[i] << "\n\n";
            }
        }


        /*
            Public Method void: calculateAvgs()

            Description:
                Method loops through the vector of vectors that holds the results of 
                all of the sorting experiments. These are averaged to get the final
                results that are then referenced when writing the final results to 
                a file.

            Params:
                - Accesses member variables

            Returns:
                - None
        */

        void calculateAvgs()
        {
            Sorts* temporary = new Sorts();
            Names = temporary->getSorts();
            delete temporary;

            results.resize(Names.size());
            Avg_Comps.resize(Names.size());

            for (int i = 0; i < averages.size(); i++)
            {
                for (int j = 0; j < averages[i].size(); j++)
                {
                    results[i] += averages[j][i];
                    Avg_Comps[i] += comps[j][i];
                }
            }

            int size = results.size();

            for (int k = 0; k < size; k++)
            {
                //cout << results[k] << " divided by " << size << endl;
                results[k] /= size;
                //cout << results[k] << endl;
                Avg_Comps[k] /= size;
            }
        }

        
        /*
            Public Method void: startExperiment()

            Description:
                Method loops through the runs variable to determine how many times to
                run the sorting experiment. Data is loaded, then the experiment is run
                and then the run time averages and computations are logged from the 
                experiment before the object is deleted and a new instance is created
                when the loop increments again.

            Params:
                - Accesses member variables

            Returns:
                - None
        */

        void startExperiment()
        {
            for (int i = 0; i < runs; i++)
            {
                Sorts* temp = new Sorts(5000);
                temp->loadData();
                temp->runExperiment();

                averages.push_back(temp->getTimes());
                comps.push_back(temp->getComps());
                delete temp;
            }
        }
};


int main()
{
    const char *header = "Name:       Byron Dowling\n"
        "Course:     5243 Algorithm Analysis\n"
        "Date:       2/25/2022\n\n"
        "Assignment: Sorting Experiment";

    SortExperiment T1000(20);       // Passing in 20 so we will run the experiment 20 times.
    T1000.startExperiment();
    T1000.calculateAvgs();
    T1000.showExperimentResults(header);

    return 0;
}
