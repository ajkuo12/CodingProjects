//
//  History.h
//  cs32p1
//
//  Created by Aaron Kuo on 4/5/21.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
    {
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        //Added private members
        char array[MAXROWS][MAXCOLS];
        int mRows;
        int mCols;
    };

#endif
