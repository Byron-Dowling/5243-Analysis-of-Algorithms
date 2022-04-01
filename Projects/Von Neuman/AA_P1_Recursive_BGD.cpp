/*
    Name:       Byron Dowling
    Course:     5243 Algorithm Analysis
    Date:       1/19/2022

    Assignment: 2D Matrix Recursion/Blob Count

        - The goal of this assignment is to build a 2D Matrix and load it up with
          input data and then traverse said matrix and determine how many blobs there
          are within the matrix. The beginning of a blob is identified by a '*' char
          and any additional asterisks that are deemed to be Von-Neumann neighbors to
          the orignal asterisk are considered to be part of the same blob. In other
          words, if we read an asterisk, and there are asterisks to the right and directly
          below the original asterisk, all three are considered part of the same "blob".
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef vector<char> vCHAR;     // typedef for a vector of characters, easier to declare of vector of vector of chars
typedef pair<int, int> PII;     // typedef for a pair of integers for easier syntax


/*
 
 $$\    $$\                           $$\   $$\                                                                 
 $$ |   $$ |                          $$$\  $$ |                                                                
 $$ |   $$ | $$$$$$\  $$$$$$$\        $$$$\ $$ | $$$$$$\  $$\   $$\ $$$$$$\$$$$\   $$$$$$\  $$$$$$$\  $$$$$$$\  
 \$$\  $$  |$$  __$$\ $$  __$$\       $$ $$\$$ |$$  __$$\ $$ |  $$ |$$  _$$  _$$\  \____$$\ $$  __$$\ $$  __$$\ 
  \$$\$$  / $$ /  $$ |$$ |  $$ |      $$ \$$$$ |$$$$$$$$ |$$ |  $$ |$$ / $$ / $$ | $$$$$$$ |$$ |  $$ |$$ |  $$ |
   \$$$  /  $$ |  $$ |$$ |  $$ |      $$ |\$$$ |$$   ____|$$ |  $$ |$$ | $$ | $$ |$$  __$$ |$$ |  $$ |$$ |  $$ |
    \$  /   \$$$$$$  |$$ |  $$ |      $$ | \$$ |\$$$$$$$\ \$$$$$$  |$$ | $$ | $$ |\$$$$$$$ |$$ |  $$ |$$ |  $$ |
     \_/     \______/ \__|  \__|      \__|  \__| \_______| \______/ \__| \__| \__| \_______|\__|  \__|\__|  \__|
                                                                                                                
                                                                                                                
                                                                                                                
 $$\   $$\           $$\           $$\       $$\                                                                
 $$$\  $$ |          \__|          $$ |      $$ |                                                               
 $$$$\ $$ | $$$$$$\  $$\  $$$$$$\  $$$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$$\                            
 $$ $$\$$ |$$  __$$\ $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  _____|                           
 $$ \$$$$ |$$$$$$$$ |$$ |$$ /  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$ |  \__|\$$$$$$\                             
 $$ |\$$$ |$$   ____|$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |       \____$$\                            
 $$ | \$$ |\$$$$$$$\ $$ |\$$$$$$$ |$$ |  $$ |$$$$$$$  |\$$$$$$  |$$ |      $$$$$$$  |                           
 \__|  \__| \_______|\__| \____$$ |\__|  \__|\_______/  \______/ \__|      \_______/                            
                         $$\   $$ |                                                                             
                         \$$$$$$  |                                                                             
                          \______/                                                                              

	Description:
		This class is the main driver for the program. It builds the 2D matrix that will simulate
        the "world" that we are looking for "blobs" within. The class will read in from a file the
        data that is to fill the 2D matrix. The way mine is set up is the matrix will be intialized
        to a default value before the data is read in and then once that data is read in, there is a 
        border around the actual blob world to assist with detecing blobs without getting an index
        out of range error. A method is present to prompt the user to type in the input file name that
        is used to fill up the matrix.

        Once the actual matrix is built and we begin traversing it to look for blobs, if an '*' is found
        it is flipped to a '#', the blob count is incremented and then we call the recursive function findBlobs.
        This function accepts an int variable to serve as the base case and also the indexes i and j to indicate
        the location within the matrix. Since we are looking for blobs by checking the cardinal directions, I
        created a vector of integer pairs to represent the 4 variations we need to apply to the matrix coordinates 
        to check if there is a blob. For example the indexes i and j + the int pair<0, 1> will check the index
        directly to the right of the indexes that were passed in. If a new '*' is discovered, we flip it to '#'
        and then that section of the function will turn around and recursively call the findBlobs function with
        its own base case information. 

        This process repeats until we have fully traversed the matrix and during the process a blob counter is 
        incremented.

	Public Methods:
		- Blob() - Default Constructor
		- void loadTable() - Initializes the matrix with file data
		- void printMatrix() - Sanity check to print the 2D Matrix
        - void writeMatrix() - Writing matrix to outfile
        - void writeMatrix(const char* h, const char* m) - overloaded method to write matrix to outfile
		- void traverseMatrix() - Starts the sequence for finding blobs
		- void findBlobs(int ct, int i, int j) - Recursive function that flips the blob characters
		- int showBlobs() - Public Method that calls the internal protected method and returns its value


	Private/Protected Methods:
		- int getBlobs() - "Getter" method with an added level of protection

	Usage:
		- This class creates an object that determines the blob count for a 2D Matrix
 */

class Blob
{
    protected:
        vector<vCHAR> Matrix;       // 2D Matrix represented as a vector of character vectors
        vector<PII> vonNeumann;     // A vector of integer pairs used for the von neuman neighbors
        int count;
        int position;
        int blobCount;
        ifstream infile;
        ofstream outfile;


        /*
            Protected Method int: getBlobs()

            Description:
                Abstracted getter method that returns the protected member
                variable blobCount

            Params:
                - Accesses member variable blobCount

            Returns:
                - blobCount
        */
       
        int getBlobs()
        {
            return blobCount;
        }

    public:

        /*
            Default constructor that will initialize some values, push the
            pair of ints to the coordinates vector, and initialize the matrix
            with a default values while loading the ifstream object with our
            txt file. I may change this later to also prompt the user to enter
            their own input file. 
        */
       
        Blob()
        {
            count = 1;
            blobCount = 0;

            /*
                Pushing the pair of ints to the coordinate vector that will
                represent the cardinal directions to test, up, down, left
                and right.
            */

            vonNeumann.push_back(make_pair(-1, 0));
            vonNeumann.push_back(make_pair(0, -1));
            vonNeumann.push_back(make_pair(1, 0));
            vonNeumann.push_back(make_pair(0, 1));

            Matrix.resize(22); // Resisizing our matrix's column amount

            // Resizing each index with the column length to get the 2D space
            for (int i = 0; i < Matrix.size(); i++)
            {
                Matrix[i].resize(22);
            }
            
            // Filling the matrix with a default character '-'
            for (int j = 0; j < Matrix.size(); j++)
            {
                for (int k = 0; k < Matrix[j].size(); k++)
                {
                    Matrix[j][k] = '-';
                }
            }
        }



        /*
            Public Method void: loadTable()

            Description:
                Loads the 2D Matrix with the values from the input txt file. There
                is code to accomodate/handle where the matrix could inadvertly be
                filled with blank spaces instead of the charactes, so if ASCII 32
                (space) is read, that value is skipped. Also a getline is used to
                capture each row of the matrix and that result is parsed before
                being inserted into the matrix. Also a late addition to this method
                was to prompt the user for the input file that is used to fill the
                matrix.

            Params:
                - Accesses member variable ifstream object

            Returns:
                - None
        */

        void loadTable(ifstream& input, ofstream& outfile)
        {
            char inFileName[40];
            char outFileName[40];

            cout << "Enter the input file name: \n";
            cin >> inFileName;

            cout << endl;

            input.open(inFileName);

            cout << "Enter the output file name: \n";
            cin >> outFileName;

            cout << endl;

            outfile.open(outFileName);


            while (!input.eof())
            {
                string temp;

                getline(input, temp, '\n');

                position = 1;

                for (int i = 0; i < temp.length(); i++)
                {
                    if (temp[i] != 32)
                    {
                        Matrix[count][position] = temp[i];
                        position++;
                    }
                }

                count++;
            }
        }



        /*
            Public Method void: printMatrix()

            Description:
                Utility method to print the Matrix. Mainly called twice to show
                the before and after results of the matrix. 

            Params:
                - Accesses member variable vector<vCHAR> Matrix

            Returns:
                - None
        */

        void printMatrix()
        {
            cout << endl;

            for (int i = 1; i < Matrix.size() - 1; i++)
            {
                for (int j = 1; j < Matrix[i].size() - 1; j++)
                {
                    cout << Matrix[i][j] << " ";
                }

                cout << endl;
            }   
        }



        /*
            Public Method void: writeMatrix()

            Description:
                Utility method to write the after version of the matrix to
                an outfile destination. 

            Params:
                - Accesses member variable vector<vCHAR> Matrix

            Returns:
                - None
        */

        void writeMatrix()
        {
            outfile << endl;

            for (int i = 1; i < Matrix.size() - 1; i++)
            {
                for (int j = 1; j < Matrix[i].size() - 1; j++)
                {
                    outfile << Matrix[i][j] << " ";
                }

                outfile << endl;
            }   

            outfile << "\nThe number of blobs is: " << showBlobs() << endl;
        }



        /*
            Public Method void: writeMatrix(const char* h, const char* m)

            Description:
                Overloaded utility method to print the Matrix. Intially called
                to write the header and message info and the before version of
                the matrix before the changes occur.

            Params:
                - Accesses member variable vector<vCHAR> Matrix

            Returns:
                - None
        */

        void writeMatrix(const char* h, const char* m)
        {
            outfile << h << endl << m << endl << endl;

            outfile << endl;

            for (int i = 1; i < Matrix.size() - 1; i++)
            {
                for (int j = 1; j < Matrix[i].size() - 1; j++)
                {
                    outfile << Matrix[i][j] << " ";
                }

                outfile << endl;
            }   
        }


        /*
            Public Method void: traverseMatrix()

            Description:
                This method is what starts the process of finding blobs and flipping
                the characters from '*' to a '#'. The traversal works the same as if
                we were printing the matrix but if we find a '*' we flip it to a '#',
                we incrememnt the blob count, and then we recursively call findBlobs()
                while passing n, i, and j with i and j being the matrix indexes and n
                starting at 4 to represent the 4 cardinal directions we're checking for
                more blobs, left, right, down, and up. n also serves as the base case
                that affects the number of recursive calls.

            Params:
                - Accesses member variable vector<vCHAR> Matrix

            Returns:
                - None
        */

        void traverseMatrix()
        {
            for (int i = 0; i < Matrix.size(); i++)
            {
                for (int j = 0; j < Matrix[i].size(); j++)
                {
                    if (Matrix[i][j] == '*')
                    {
                        blobCount++;
                        Matrix[i][j] = '#';

                        int n = 4;

                        while (n > 0)
                        {
                            findBlobs(n, i, j);
                            n--;
                        }
                    }
                }
            }   
        }



        /*
            Public Method void: findBlobs(int ct, int i, int j)

            Description:
                Recursive method that accepts a count variable as well as indexes
                i and j to know what position of the matrix we are working with. The
                method declares a temp coordinate pair that pulls from the vector of
                pairs using the ct variable. As the method is recursively called, there
                are different pairs that are pulled that help us modify the matrix indexes
                so that we can check all of the cardinal directions around the orginal
                position. The method works similar to the traverseMatrix one in that if a
                '*' is discovered we flip it to a '#' and then we have to recursively check
                that index as well by calling the same findBlobs from within itself.

            Params:
                - Accesses member variable vector<vCHAR> Matrix
                - int ct: used to keep track of base case and index of int pairs vector
                - int i, int j: 2D matrix position

            Returns:
                - None
        */

        void findBlobs(int ct, int i, int j)
        {
            PII temp = vonNeumann[ct - 1];

            i = i + temp.first;
            j = j + temp.second;

            if (Matrix[i][j] == '*')
            {
                Matrix[i][j] = '#';

                int n = 4;

                while (n > 0)
                {
                    findBlobs(n, i, j);
                    n--;
                }
            }
        }



        /*
            Public Method int: showBlobs()

            Description:
                Abstracted getter method that calls a protected method that will
                actually return the value we are needing to access.

            Params:
                - Indirecxtly accesses member variable blobCount

            Returns:
                - blobCount
        */

        int showBlobs()
        {
            return getBlobs();
        }
};


int main()
{
    Blob B1;                // New Blob Object
    ifstream in;
    ofstream out;

    const char *header = "Name:       Byron Dowling\n"
        "Course:     5243 Algorithm Analysis\n"
        "Date:       1/11/2022\n\n"
        "Assignment: 2D Matrix Recursion/Blob Count";

    const char *message = "The goal of this assignment is to build a 2D Matrix and load it up with"
          " input data and then traverse said matrix and determine how many blobs there"
          " are within the matrix. The beginning of a blob is identified by a '*' char"
          " and any additional asterisks that are deemed to be Von-Neumann neighbors to"
          " the orignal asterisk are considered to be part of the same blob. In other"
          " words, if we read an asterisk, and there are asterisks to the right and directly"
          " below the original asterisk, all three are considered part of the same blob.";

    // Loading up the matrix and showing the before result

    cout << header << endl << message << endl << endl;
    B1.loadTable(in, out);
    cout << endl;
    B1.printMatrix();
    B1.writeMatrix(header, message);
    
    cout << endl;

    // Calling the methods to flip the '*' to '#' and then print
    B1.traverseMatrix();
    B1.printMatrix();
    B1.writeMatrix();
    
    // Showing the final blob count
    cout << "\nThe number of blobs is: " << B1.showBlobs() << endl;



    return 0;
}
