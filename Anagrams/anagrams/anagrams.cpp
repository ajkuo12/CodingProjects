#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;
const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


// makeDictionary ----
//Puts each string in dictfile into the array dict. Returns the number of words
//read into dict. This number should not be larger than MAXDICTWORDS since that is
//the size of the array.
int makeDictionary(istream &dictfile, string dict[]){
    //Extracts data from dictfile until EOF (end-of-file)
    if (dictfile.eof()) {
        return 0;
    }
    //Inserts data into string
    string data;
    dictfile >> data;
    // Start a count for every word added
    int currentWord = makeDictionary(dictfile, dict);
    // Stop adding if amount of words,
    if (currentWord <= MAXDICTWORDS) {
        dict[currentWord] = data;
        currentWord++;
        return currentWord;
    } else
        return MAXDICTWORDS;
}

// revealOutcomes ----
//Displays size number of strings from results. The results can be printed in
//any order
void revealOutcomes(const string results[], int size) {
    if (size-1 < 0)
            return;
    cout << "Matching word " << results[size - 1] << endl;
    revealOutcomes(results, size-1);
}

// checkResults ----
// This helper function checks to see if the word is already in the results or not. Duplicate checker.
bool checkResults(const string results[], int size, const string word){
    // Base Case: If size is 0, return true, no duplicates
    if (size == 0)
        return true;
    // If duplicate, return false
    if (word == results[0])
        return false;
    else
        // Keep recursing through results
        return checkResults(results+1, size-1, word);
}

// anagram ----
// This helper function check to see if the word is an an anagram by comparing a given character position in the inputted word to each character of a dictionary word of matching length. If a letter cannot be found in the dictionaryWord, it is not an anagram.
bool anagram(const string word, string dictionaryWord, const int& index, const int& indexD){
    int check = 0;
    // If recursed through entire dictionary word and no match, not anagram
    if (indexD == word.size() && check == 0)
        return false;
    // If there is a match in letters, return true
    if (word.substr(index,1) == dictionaryWord.substr(indexD,1)){
        check++;
        return true;
    }
    else
        // Keep recursing through entire dictionary word
        return (anagram(word, dictionaryWord, index, indexD + 1));
}

// allMatch ----
// This helper function basically recurses to use the anagram function the same amount of times as there are characters in the word.
bool allMatch(const string word, const string dict[], int count){
    //If count is equal to size of word, the word is an anagram
    if (count == word.size())
        return true;
    else
        // If the anagram function returns false, not an anagram
        if (anagram(word, dict[0], count, 0) == false){
            return false;
        }
    //Keeps recursing through each character
    return (allMatch(word, dict, count+1));
}

// mainCheck ----
// This helper function is essentially the most important function as it handles all helper functions and determines if a word is an anagram or not.
int mainCheck(const string& word,const string dict[], int size, string results[], int &check) {
    //Base Case: If size is 0, return number of matched cases
    if (size == 0)
        return check;
    //Easy checks to determine if anagram or not to make the program more efficient
    // 1.) If size of inputted word is not equal to dictionary word, NOT anagram
    // 2.) If word is already in the results, no need to add duplicate
    // 3.) If first letter of inputted word is found in dictionary word, possibly anagram
    if (dict[0].size()==word.size() && checkResults(results, check, dict[0]) && anagram(word, dict[0], 0, 0)){
        // This function recurses through each and every letter if the dictionary word passes through the easy checks to determine if the word really is an anagram or not
        if (allMatch(word, dict, 0)==true)
            // If true, add dictionary word to results as it is an anagram
            results[check++] = dict[0];
    }
    // Keep iterating through dictionary until depleted
        return mainCheck(word, dict+1, size-1, results, check);
}

// shuffleChars ----
//Puts all the possibilities of word which are found in dict into results. Returns
//the number of matched words found. This number should not be larger than
//MAXRESULTS since that is the size of the array. The size is the number of words
//inside the dict array.
int shuffleChars(const string& word,const string dict[], int size, string results[]) {
    int check = 0;
    return mainCheck(word, dict, size, results, check);
}

// MAIN
int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    // Change to wherever the words.txt in other computers
    dictfile.open("/Users/aaronkuo/Desktop/anagrams/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = makeDictionary(dictfile, dict);
    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = shuffleChars(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        revealOutcomes(results, numMatches);
    return 0;
}
