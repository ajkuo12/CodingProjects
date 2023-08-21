//
//  WordTree.h
//  Trees
//
//  Created by Aaron Kuo on 8/14/21.
//

#ifndef WordTree_h
#define WordTree_h

#include <stdio.h>
#include <iostream>
#include <string>

typedef std::string WordType;

struct WordNode {
// Declaration
     WordType m_data;
     WordNode *m_left;
     WordNode *m_right;
     int counter;
// Constructor
    WordNode(WordType data){
        m_data = data;
        m_left = nullptr;
        m_right = nullptr;
        counter = 1;
    }
    friend std::ostream& operator << (std::ostream &out, const WordNode &n);
};

class WordTree {
 private:
    WordNode *root;
    // Private Functions
    void clear(WordNode *k);
    int distinctRecursion(WordNode* sub) const;
    int totalRecursion(WordNode* sub) const;
 public:
     // default constructor
     WordTree() : root(nullptr) { };

     // copy constructor
     WordTree(const WordTree& rhs);

     // assignment operator
     const WordTree& operator=(const WordTree& rhs);
     // Inserts v into the WordTree
     void add(WordType v);
     // Returns the number of distinct words / nodes
     int distinctWords() const;
     // Returns the total number of words inserted, including
     // duplicate values
     int totalWords() const;

     // Prints the WordTree
     friend std::ostream& operator<<(std::ostream &out, const
    WordTree& rhs);
     // Destroys all the dynamically allocated memory in the
     // tree
     ~WordTree();
};
#endif /* WordTree_h */
