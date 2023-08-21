//
//  main.cpp
//  covid
//
//  Created by Aaron Kuo on 2/1/21.
//

// Libraries
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

// Namespace
using namespace std;

// Functions
bool isValidResultString(string results);
int positiveTests(string results);
int negativeTests(string results);
int totalTests(string results);
int batches(string results);
int extractNumber( string results, size_t& index, bool& isValid );



int main() {
    
    // String
    string results = "R1251+252-999";
    
    // Results of Program
    bool VT = isValidResultString(results);
    cout << VT << " Validity" << endl;
    int PosTest = positiveTests(results);
    cout << PosTest << " Positive Tests" << endl;
    int NegTest = negativeTests(results);
    cout << NegTest << " Negative Tests" << endl;
    int batchNumber = batches(results);
    cout << batchNumber << " Batches" << endl;
    int Total = totalTests(results);
    cout << Total << " Total Tests" << endl;
    return 0;
}



// Function -- Extract Numbers from Strings
// Function provided from professor, no edits were made.
int extractNumber( string results, size_t& index, bool& isValid )
{
    // track the integer value found
    int quantity( 0 );
    // the result isn't valid until we actually extract atleast one digit!
    isValid = false;
    // don't go beyond the string!
    if (index < results.length())
    {
        // the number can't start with a zero!
        if (results[index] >= '1' && results[index] <= '9')
        {
            // the number should be made up of digits
            while( index < results.length()  &&  isdigit( results[ index ] ) )
            {
                // extract one digit and add it to the cumulative value held in quantity
                int digit = results[ index ] - '0';
                quantity = quantity * 10 + digit;
                index = index + 1;
                isValid = true;
            }
        }
        else
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return( quantity );
}

// Function -- Verifying Validity of String Format
// Using a series of tests, this function will verify that the
// string is in the correct format.
bool isValidResultString(string results)
{
    // Initializing Variables
    int total1 = 0;
    int Rcounter = 0;
    int plusCounter = 0;
    int minCounter = 0;
    int PosTest = 0;
    int NegTest = 0;
    int TotTest = 0;
    
    // Initializing Local Variables
    size_t ind = 0;
    bool Valid = true;
    
    // Test 1: Checking for Blank Entry
    // Most basic test. Checking if string is empty.
    string::size_type sizeString = results.size();
    if (sizeString <1){
        return false;
    }
    else{}
    
    // Test 2: Checking for Invalid Characters
    // If any of the characters in the string are not valid, the string is automatically invalid.
    for (size_t k = 0; k != results.size(); k++){
        if (results[k] !=  'R' && results[k] != '+' && results[k] != '-' &&
            results[k] != '0' && results[k] != '1' && results[k] != '2' &&
            results[k] != '3' && results[k] != '4' && results[k] != '5' &&
            results[k] != '6' && results[k] != '7' && results[k] != '8' &&
            results[k] != '9'){
            return false;}
        else{}
    }
    
    // R Counter
    // Counting number of R to determine number of batches.
    for (size_t k = 0; k != results.size(); k++){
        if (results[k] == 'R')
            Rcounter++;
        else {}
    }
   
    // Test 3: Checking for First Letter R and Second Digit
    // Another basic test. If first character of string is not R, string is invalid.
    // Similarly, if second character is not a digit, string is invalid.
    char firstLetter = results.at(0);
    if (firstLetter == 'R')
    {}
    else
    {
        return false;
    }
    if (results[1] >= '1' && results[1] <= '9'){
       total1 = (results[1] - 48);
    }
    else
    {
        return false;
    }
    
    // Test 4: Checking for Duplicate Signs and Leading Zeros
    // Using the R Counter, the number of plus/minus signs should be equal to
    // the amount of R's. If there is any discrepancy, string is invalid.
    // If there is a "0" in the string, the number next to it cannot be 0
    // or else it becomes a leading 0, making the string invalid.
    for (size_t k = 0; k != results.size(); k++){
        if (results[k] == '+') // Counting number of "+"
            plusCounter++;
        else
        {}
        if (results[k] == '-') // Counting number of "-"
            minCounter++;
        else
        {}
        if (results[k] == '0') // Checking for leading zeros
            if (results[k+1] >= '1' && results[k+1] <= '9'){
                return false;
                }
            else {}
        else{}
    }
    if (Rcounter == plusCounter && Rcounter == minCounter) // Comparing Sign count with R count
    {}
    else{
        return false;
    }
    
    
    // Test 5: Checking if Test Results add up
    // This test checks for either "R","+", or "-" and collects the number after it and adds it
    // to its specific counter. This acts as the counter for each test. After counting all the
    // tests, the program adds up the positive and negative tests to verify that it equals
    // total tests. If not, the string is invalid.
    for (size_t k = 0; k != results.size(); k++){
        if (results[k] == 'R'){                 // Counting Total tests
             if (results[k+1] >= '1' && results[k+1] <= '9'){
                 ind = k + 1;
                 if (PosTest + NegTest == TotTest){ //Checking to see if tests add up after every batch
                     if (TotTest == 0){
                         int res = extractNumber(results, ind, Valid);
                         TotTest = res;
                     }
                     else{
                         int res = extractNumber(results, ind, Valid);
                         TotTest = res + TotTest;
                     }
                 }
                 else{
                     return false;}
                 }
             else{
                 return false;}
        }
        else{}
       if (results[k] == '+')                  // Counting Positive tests
            if (results[k+1] >= '0' && results[k+1] <= '9'){
                ind = k + 1;
                if (PosTest == 0){
                int resP = extractNumber(results, ind, Valid);
                    PosTest = resP;
                }
                else{
                    int resP = extractNumber(results, ind, Valid);
                    PosTest = PosTest + resP;
                }
            }
            else{
                return false;}
        else{}
        if (results[k] == '-')                // Counting Negative tests
            if (results[k+1] >= '0' && results[k+1] <= '9'){
                ind = k + 1;
                if (NegTest == 0){
                    int resN = extractNumber(results, ind, Valid);
                        NegTest = resN;                }
                else{
                    int resN = extractNumber(results, ind, Valid);
                    NegTest = NegTest + resN;
                }
            }
            else{
                return false;}
        else{}
    }
    if (PosTest + NegTest == TotTest)   // Checking if tests add up
    {}
    else{
        // If tests don't add up, invalid string
        return false;}
    
    // Valid String
    // If the string makes it to here, it is a valid string.
        return true;
}

// Function -- Gathering total number of Positive Tests
// Using the Validity function, this function will gather the total number of positive tests
// if the string is in valid format. If not, this function returns -1.
int positiveTests(string results)
{
    
    // Initializing local variables
    bool validityTest = isValidResultString(results);
    bool Valid = true;
    int PosTest = 0;
    size_t ind = 0;

    // If string is valid, function uses extractNumber function to collect the number of positive tests
    // after every "+" sign. Function then returns the value of positive tests
    if (validityTest==true){
        for (size_t k = 0; k != results.size(); k++){
            if (results[k] == '+'){
                ind = k + 1;
                    if (PosTest == 0){
                        int resP = extractNumber(results, ind, Valid);
                        PosTest = resP;
                        }
                    else{
                        int resP = extractNumber(results, ind, Valid);
                        PosTest = PosTest + resP;}
                    }
            else{}
        }
        return PosTest;
        }
    // If string is not valid, function returns -1.
        else{
            return -1;
    }
}

// Function -- Gathering total number of Negative Tests
// Using the Validity function, this function will gather the total number of negative tests
// if the string is in valid format. If not, this function returns -1.
int negativeTests(string results)
{
    // Initializing local variables
    bool Valid = true;
    bool VT = isValidResultString(results);
    int NegTest = 0;
    size_t ind = 0;
        
    // If string is valid, function uses extractNumber function to collect the number of positive tests
    // after every "+" sign. Function then returns the value of positive tests
    if (VT == true){
        for (size_t k = 0; k != results.size(); k++){
            if (results[k] == '-'){
                ind = k + 1;
                    if (NegTest == 0){
                        int resN = extractNumber(results, ind, Valid);
                        NegTest = resN;
                        }
                        else{
                            int resN = extractNumber(results, ind, Valid);
                            NegTest = NegTest + resN;}
                        }
            else{}
    }
        return NegTest;
        }
    // If string is not valid, function returns -1.
        else{
            return -1;
        }
}

// Function -- Gathering Total Number of Batches
// This function uses the number of R's present in a valid string to determine
// the total amount of batches in a string and returns that value. If the string is
// invalid, this function returns the value -1.
int batches(string results)
{
    // Initializing Local Variables
    int Rcounter = 0;
    bool VT = isValidResultString(results);
        // Function loops through string, counting number of occurences of "R"
        if (VT == true){
        for (size_t k = 0; k != results.size(); k++){
            if (results[k] == 'R')
                Rcounter++;
            else {}
        }
        return Rcounter;
        }
        // If string is invalid, function returns -1.
        else{
            return -1;
        }
}

// Function -- Gathering Total Number of Tests
// This function gathers the total number of tests from all available batches by
// recording the number of tests after the R character and returns the sum of those
// values. If the string is invalid, the function returns -1.
int totalTests(string results)
{
    // Initializing Local Variables
    bool VT = isValidResultString(results);
    bool Valid = true;
    int TotTest = 0;
    size_t ind = 0;
    // If string is valid, function loops through string adding up number of total tests.
        if (VT == true){
        for (size_t k = 0; k != results.size(); k++){
            if (results[k] == 'R'){
                     ind = k + 1;
                     if (TotTest == 0){
                         int res = extractNumber(results, ind, Valid);
                         TotTest = res;
                     }
                     else{
                         int res = extractNumber(results, ind, Valid);
                         TotTest = res + TotTest;
                     }
            }
             else{}
        }
        return TotTest;
    }
    // If string is invalid, function returns -1.
        else{
            return -1;
        }
}

