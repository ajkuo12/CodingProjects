#include "History.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor
History::History( int nRows, int nCols)
       :mRows(nRows), mCols(nCols)
{
    // Iterate through the board and initialize with '.'
    for (int i = 0; i < mRows; i++){
        for (int j = 0; j < mCols; j++){
            array[i][j] = '.';
        }
    }
}

// Record boolean
// Check first if specifications are true
// Then change value of each position based on flatulent interaction given
// from the city class
bool History::record(int r, int c)
{
    if (r<1 || c<1 || r>mRows || c>mCols ){
        return false;
    }
    else{
        char pos = array[r-1][c-1];
                if (pos >= 'A' && pos <= 'Z')
                {
                    pos += 1;
                }
                else if (pos >= 'Z')
                {
                    pos = 'Z';
                }
                else
                {
                    array[r - 1][c - 1] = 'A';
                }
                return true;
    }
}

// Display Function
// Clears screen and displays the interactions recorded in the Record function
void History::display() const
{
    clearScreen();
    for (int i = 0; i < mRows; i++)
        {
            for (int j = 0; j < mCols; j++)
            {
                cout << array[i][j];
            }
            cout << '\n';
        }
        
        cout << '\n';
    }


