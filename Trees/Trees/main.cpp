#include "WordTree.h"
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int main ()
{
    WordTree k;
    // Add Test Words
    k.add("Kim");
    k.add("Kanye");
    k.add("kourtney");
    k.add("kris");
    k.add("Kris");
    k.add("kim");
    k.add("Kourtney");
    k.add("Kris");
    k.add("Kylie");
    // Print Out Parameters
    cout << k << endl;
    cout << k.distinctWords() << " Distinct" << endl;
    cout << k.totalWords() << " Total" << endl;
    return 0;
}

