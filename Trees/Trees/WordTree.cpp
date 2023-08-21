//
//  WordTree.cpp
//  Trees
//
//  Created by Aaron Kuo on 8/16/21.
//

#include "WordTree.h"
using namespace std;

// Copy Constructor
WordTree::WordTree(const WordTree& rhs){
    *this = rhs;
}

// Assignment Operator
const WordTree& WordTree::operator=(const WordTree& rhs) {
    if (rhs.root == nullptr){
        root = nullptr;
    }
    else
        root = new WordNode(*rhs.root);
        return *this;
    }

// Add Words
void WordTree::add(WordType v){
    // If tree is empty, add word as new root
    if (root == nullptr)
        root = new WordNode(v);
    else
    {
        WordNode *k = root;
        while (k != nullptr){
            // If string is equal to existing string
            if (k -> m_data == v){
                // Add to counter
                k -> counter++;
                return;
            }
            // If node is greater than inserted string
            else if(k->m_data > v){
                // Create new node
                if (k -> m_left == nullptr)
                {
                    k -> m_left = new WordNode(v);
                    return;
                }
                // Iterate
                else
                    k = k-> m_left;
            }
            // Node is less than inserted string
            else{
                // Create new node
              if(k -> m_right == nullptr)
                {
                    k -> m_right = new WordNode(v);
                    return;
              }
                // Keep Iterating
              else
                  k = k -> m_right;
            }
        }
    }
}

// Both Functions Rely on their respective Private Member Functions
int WordTree::distinctWords() const
{
    return distinctRecursion(root);
}
int WordTree::totalWords() const
{
    return totalRecursion(root);
}

// Destructor
WordTree::~WordTree()
{
    clear(root);
}

// Both are needed to print results correctly
// Word Tree Printer
std::ostream& operator<<(std::ostream &out, const WordTree& rhs)
{
if(rhs.root != nullptr){
        out << *rhs.root;
    }
return out;
  
}
// Word Node Printer
std::ostream& operator << (std::ostream &out, const WordNode &n)
{
    if( n.m_left != nullptr ){
        out << *n.m_left;
    }
    if( n.m_right != nullptr ){
        out << *n.m_right;
    }
    out << n.m_data << " " << n.counter << endl;

    return out;
}


// Private Member Functions

// Distinct Recursion
// Does the actual work to determine number of distinct string values
int WordTree::distinctRecursion(WordNode* temp) const
{
    // Return if no more leaves
    if (temp== nullptr)
        return 0;
    // Count and Add Up Children of Root Nodes
    return (distinctRecursion(temp -> m_left) + distinctRecursion(temp -> m_right) + 1);
}
// Total Recursion
int WordTree::totalRecursion(WordNode* temp) const
{
    // Return if no more nodes
    if (temp == nullptr)
        return 0;
    // Count and Add Up all Nodes including duplicates
    return (totalRecursion(temp -> m_left) + totalRecursion(temp -> m_right) + temp -> counter );
}
// Destructor
void WordTree::clear(WordNode *k)
{
// If already empty, return
if(k == nullptr)
    return;
// Delete
else
    clear(k->m_left);
    clear(k->m_right);
delete k;
}
