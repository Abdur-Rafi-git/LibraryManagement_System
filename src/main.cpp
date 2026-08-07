#include <iostream>
#include "Library.h"
using namespace std;

int main() {
    Library library;
    
    // Load data from files
    library.loadAllData();
    
    cout << "\nLibrary system ready!\n" << endl;
    
    library.run();
    
    // Save data before closing
    library.saveAllData();
    
    return 0;
}