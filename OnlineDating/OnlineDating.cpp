//
//  OnlineDating.cpp
//  Project2
//
//  Created by Aaron Kuo on 7/13/21.
//

#include "OnlineDating.h"
#include <string>
#include <iostream>
using namespace std;


// Default Constructor
OnlineDating::OnlineDating() {
    // Initializing private members
    head = nullptr;
    tail = nullptr;
    mItems = 0;
}

// Copy Constructor
OnlineDating::OnlineDating(const OnlineDating& other) {
    // Initializing private members
    head = nullptr;
    tail = nullptr;
    mItems = 0;
    // Using other object to initialize list
    // If other string has items in it
    if (other.mItems > 0){
            string first;
            string last;
            OnlineType value;
        // Traverse through the other list and copy it over using private member functions get and insert
        for (int i = 0; i < other.mItems; i++){
                other.get(i,first, last, value);
                insert(first, last, value);
        }
    }
}

// Destructor
OnlineDating::~OnlineDating(){
    Node* ptr = head;
    // Traversing through list
    while (ptr!= nullptr){
            // Deallocation
            Node *temp = ptr -> next;
            delete ptr;
            ptr = temp;
        }
    }

// Assignment Operator
OnlineDating& OnlineDating::operator=(const OnlineDating& other){
    // If other list is exactly same
    if (&other == this){
        return (*this);
    }
    // If current list has nodes
    if (mItems > 0){
        Node *ptr = head;
            // Delete nodes
            while (ptr != nullptr){
                Node *temp = ptr-> next;
                delete ptr;
                ptr = temp;
            }
        // Reinitialize
        head = nullptr;
        tail = nullptr;
        mItems = 0;
}
    // Assign items from the other list
    if (other.mItems > 0){
        string first;
        string last;
        OnlineType value;
        for (int i = 0; i < other.mItems; i++){
            other.get(i,first, last, value);
            insert(first, last, value);
        }
    }
    return *this;
}

// no Matches function
bool OnlineDating::noMatches() const {
    // If start of the list is nullptr, indicates that the entire list is empty
    if (head == nullptr)
        return true;
    else
        return false;
}

// how Many Matches function
int OnlineDating::howManyMatches() const {
    // Initalize local variable and node
    Node* k = head;
    int count = 0;
    // Traverse through list
    while (k != nullptr){
        // for every node, add to counter
        count++;
        k = k -> next;
    }
    // return number fo nodes in list
    return count;
}

// make Match function
bool OnlineDating::makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value){
    // If there are no items in the list
    if (mItems == 0) {
        head = new Node;
            // Add item to list
               tail = head;
               head -> first = firstName;
               head -> last = lastName;
               head -> value = value;
               head -> next = nullptr;
               head -> prev = nullptr;
        // If there are items in the list already
       } else {
           Node* ptr = head;
           // If first node has name equal to current name, return false since name is already in list
           if (ptr -> first == firstName && ptr -> last== lastName)
               return false;
           // Traverse through list
           while (ptr -> next != nullptr) {
               // If any node is equal to full name, return false
               if (ptr -> first == firstName && ptr -> last== lastName)
                   return false;
               ptr = ptr->next;
           }
           ptr -> next = new Node;
           ptr -> next -> first = firstName;
           ptr -> next -> last = lastName;
           ptr -> next -> value = value;
           ptr -> next -> next = nullptr;
           ptr -> next -> prev = ptr;
           tail = ptr -> next;
           }
       mItems++;
       return true;
   }

// transform Match function
bool OnlineDating::transformMatch(const std::string& firstName, const std::string& lastName, const OnlineType & value){
    // If no items in list, return false
    if (mItems == 0)
        return false;
    Node* ptr = head;
    // Traverse through list
    for (int i = 0; i < mItems; ptr = ptr -> next, i++){
        // If name matches, change original value to new value and return true
        if (ptr->first == firstName && ptr -> last == lastName){
            ptr->value = value;
            return true;
        }
    }
    // if no match, return false
    return false;
}

// make or Transform list
bool OnlineDating::makeOrTransform(const std::string& firstName, const
                                   std::string& lastName, const OnlineType& value){
    // If no items in list, add as new node
    if (mItems == 0){
        head = new Node;
        tail = head;
        head -> first = firstName;
        head -> last = lastName;
        head -> value = value;
        head -> next = nullptr;
        head -> prev = nullptr;
        return true;
    }
    // Traverse through list
    Node* ptr = head;
    for (int i = 0; i < mItems; ptr = ptr -> next, i++){
        // If match, transform value and return true
        if (ptr->first == firstName && ptr -> last == lastName){
            ptr->value = value;
            return true;
        }
    }
    // If no match, add new node with values and return true
    makeMatch(firstName,lastName,value);
    return true;
}

// block Previous Match function
bool OnlineDating::blockPreviousMatch(const std::string& firstName, const
                                      std::string& lastName){
    if (mItems == 0)
        return false;
    Node* ptr = head;
    for (int i = 0; i < mItems; ptr = ptr -> next, i++){
        if (ptr->first == firstName && ptr -> last == lastName){
            // If the item to be deleted is the first in the list
            if(i == 0){
                // If there are multiple nodes in the list
                if(ptr -> next != nullptr){
                    head = ptr->next;
                    ptr -> next -> prev = nullptr;
                    delete ptr;
                    mItems--;
                    return true;
                }
                // If there is only one node in the list
                else{
                    head = tail = nullptr;
                    delete ptr;
                    mItems--;
                    return true;
                }
            }
            // If the item to be deleted is last in list
            if (i == mItems){
                ptr -> prev -> next = nullptr;
                tail = ptr-> prev;
                delete ptr;
                mItems--;
                return true;
            }
            // Item to be deleted is not first or last in list
            else{
                ptr-> prev -> next = ptr -> next;
                ptr -> next -> prev = ptr-> prev;
                delete ptr;
                mItems--;
                return true;
            }
        }
    }
    return false;
}

// someone Among Matches function
bool OnlineDating::someoneAmongMatches(const std::string& firstName, const
                                       std::string& lastName) const {
    // If empty list, return false
    if (head == nullptr)
        return false;
    Node* ptr = head;
    // Traverse through list
    for (int i = 0; i < mItems; ptr = ptr -> next, i++){
        // If full name matches name in list, return true
        if (ptr->first == firstName && ptr -> last == lastName){
            return true;
        }
    }
    // If no match, return false
        return false;
}

//look at Matches function
bool OnlineDating::lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const{
    // If empty list, return false
    if (head == nullptr)
        return false;
    Node* ptr = head;
    // traverse through list
    for (int i = 0; i < mItems; ptr = ptr -> next, i++){
        // If full name matches name in list, switch value to new value and return true
        if (ptr->first == firstName && ptr -> last == lastName){
            ptr -> value = value;
            return true;
        }
    }
    // if no match, return false
    return false;
}

bool OnlineDating::confirmMatch(int i, std::string& firstName, std::string&
                                lastName, OnlineType & value) const{
    // incomplete but compiles
    Node* ptr = head;
    if (i >= 0 && i < mItems){
        for (int j = 0; j < i; ptr = ptr -> next, j++){
                
            }
        return true;
    }
    return false;
}

// trade Matches function
void OnlineDating::tradeMatches(OnlineDating& other){
    // Switch number of items in the list
    int k = other.mItems;
    other.mItems = this -> mItems;
    this -> mItems = k;
    // Switch head node between lists
    Node* p;
    p = other.head;
    other.head = head;
    head = p;
    // Switch tail node between lists
    Node* q;
    q = other.tail;
    other.tail = tail;
    tail = q;
}

void OnlineDating::printList() const
{
    for (Node *p = head; p != nullptr; p = p->next){
    cout << p-> first << " " << p-> last << " " << p -> value << " ";
    cout << endl;
    }
    return;
}

// Private Memeber Functions

bool OnlineDating::get(int i, std::string& firstName, std::string& lastName, OnlineType& value)const{
    
    if (!(i >= 0 && i < mItems))
        return false;
    
    Node* ptr = head;
    int count = 0;
    if (i == count) {
        firstName   = ptr -> first;
        lastName    = ptr -> last;
        value       = ptr->value;
        return true;
    }
    
    while (ptr->next != nullptr) {
        ptr = ptr->next;
        count++;
        if (i == count) {
            firstName = ptr -> first;
            lastName  = ptr -> last;
            value     = ptr -> value;
            return true;
        }
    }
    return false;
}

bool OnlineDating::insert(std::string& firstName, std::string& lastName, const OnlineType& value) {
    if (mItems == 0) {
        head = new Node;
        tail = head;
        head -> first = firstName;
        head -> last = lastName;
        head -> value = value;
        head -> next = nullptr;
        head -> prev = nullptr;
    } else {
        Node* ptr = head;
        while (ptr-> next != nullptr){
            if (lastName > ptr -> last){
                ptr = ptr -> next;
            }
            else{
                ptr -> next = new Node;
                ptr -> next -> first = firstName;
                ptr -> next -> last = lastName;
                ptr -> next -> value = value;
                ptr -> next -> next = nullptr;
                ptr -> next -> prev = ptr;
                tail = ptr -> next;
            }
        }
    }
    mItems++;
    return true;
}

// Non - Member Functions

bool mergeMatches(const OnlineDating & odOne,const OnlineDating & odTwo, OnlineDating & odJoined){
    OnlineDating combinedList = *new OnlineDating;
    //incomplete but compiles
    combinedList = odOne;
    for (int i = 0; i<odTwo.howManyMatches(); i++){
        
    }
    return true;
}

void authenticateMatches (const std::string& fsearch, const std::string& lsearch, const OnlineDating& odOne,
                          OnlineDating& odResult){
    // incomplete but compiles
}
