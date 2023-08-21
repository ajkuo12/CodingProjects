//
//  main.cpp
//  Project2
//
//  Created by Aaron Kuo on 7/13/21.
//

#include <iostream>
#include <string>
#include "OnlineDating.h"
#include <cassert>
using namespace std;

int main() {

//// For Default Constructor
//    OnlineDating glee;
//    //--------For an empty list--------
//    // Test Size
//    assert(glee.howManyMatches()==0);
//    // Test Empty
//    assert(glee.noMatches());
//    // Test no match to block
//    assert(!glee.blockPreviousMatch("Finn", "Hudson"));
    
//    // For Copy Constructor
//    OnlineDating glee;
//    glee.makeMatch("Rachel", "Berry", 12);
//    OnlineDating fox = glee;
//    assert(glee.howManyMatches()==1);
//    // Test if items copy over
//    assert(fox.howManyMatches()==1);

    
//    // No Matches
//    OnlineDating glee;
//    // Check list has no items
//    assert(glee.noMatches());
//    glee.makeMatch("Blaine", "Anderson", 100);
//    // Check list has match
//    assert(!glee.noMatches());
    
//    // how Many Matches
//    OnlineDating glee;
//    // No Matches
//    assert(glee.howManyMatches()==0);
//    glee.makeMatch("Kurt", "Hummel", 9);
//    glee.makeMatch("Sam", "Evans", 67);
//    // Check how many items
//    assert(glee.howManyMatches()==2);
//    glee.blockPreviousMatch("Kurt", "Hummel");
//    // Check item count if removal
//    assert(glee.howManyMatches()==1);

//    // make Matches
//    OnlineDating glee;
//    glee.makeMatch("Santana", "Lopez", 11);
//    // Cannot add duplicates
//    assert(!glee.makeMatch("Santana", "Lopez", 11)==true);
//    // Add same Last Name
//    glee.makeMatch("Matt", "Lopez", 12);
//    assert(glee.howManyMatches()==2);
//    // ! Will fail alphabetical test cases, code can't sort !
    
//    OnlineDating glee;
//    glee.makeMatch("Tina", "Chen", 23);
//    // Check if working
//    assert(glee.transformMatch("Tina", "Chen", 5)==true);
//    // Check if no matching name
//    assert(glee.transformMatch("Artie", "Abrams", 21)==false);
    
//    //make or Transform
//    OnlineDating glee;
//    // Add if empty list
//    assert(glee.makeOrTransform("Jake", "Puckerman", 3)==true);
//    assert(glee.howManyMatches()==1);
//    // Transform number if same name
//    assert(glee.makeOrTransform("Jake", "Puckerman", 5)==true);
//

//    // block Previous Match
//    OnlineDating glee;
//    // blocks matching name
//    glee.makeMatch("Quinn", "Fabray", 42);
//    glee.makeMatch("Mercedes", "Jones", 85);
//    glee.blockPreviousMatch("Quinn", "Fabray");
//    assert(glee.howManyMatches()==1);
//    // No change if name does not match
//    glee.blockPreviousMatch("Puckerman", "Puck");
//    assert(glee.howManyMatches()==1);
    
//    // someone Among Matches
//    OnlineDating glee;
//    glee.makeMatch("Will", "Schuester", 543);
//    glee.makeMatch("Sebastian", "Smythe", 314);
//    glee.makeMatch("Kitty", "Wilde", 312);
//    // True if name matches
//    assert(glee.someoneAmongMatches("Kitty", "Wilde")==true);
//    // False if name does not match
//    assert(glee.someoneAmongMatches("Mike", "Chang")==false);

//    // look at Matches
//    OnlineDating glee;
//    int h= 99;
//    glee.makeMatch("Becky", "Jackson", 90);
//    glee.makeMatch("Sugar", "Motta", 45);
//    // False if no name match
//    assert(glee.lookAtMatches("Joe", "Hart", h)==false);
//    // True if name match
//    assert(glee.lookAtMatches("Sugar", "Motta", h)==true);
    
//    // trade Matches
//    OnlineDating glee;
//    OnlineDating awkward;
//    awkward.makeMatch("Jenna", "Hamilton", 5);
//    glee.tradeMatches(awkward);
//    // Switching lists
//    assert(glee.howManyMatches()==1);
    
}



