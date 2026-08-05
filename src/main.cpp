#include <iostream>
#include "Library.h"
using namespace std;

int main() {
    Library library;
    
    cout << "Loading sample data...\n" << endl;
    library.addBook("The C++ Programming Language", "Bjarne Stroustrup", "Computer Science", 5);
    library.addBook("Grokking Algorithms", "Aditya Bhargava", "DSA", 3);
    library.addBook("Hamlet", "William Shakespeare", "English Literature", 4);
    library.addBook("Pather Panchali", "Bibhutibhushan Bandyopadhyay", "Bangla Literature", 6);
    library.addBook("The Cruel Birth of Bangladesh", "Archer Blood", "Bangladesh History", 2);
    
    cout << "Registering sample users...\n" << endl;
    library.registerUser("Taseen", "01712345678", "CSE-56");
    library.registerUser("Sadia", "01987654321", "CSE-56");
    library.registerUser("Saon", "01555555555", "CSE-56");
    library.registerUser("Cristiano", "01666666666", "ENG-64");
    library.registerUser("Messi", "01777777777", "ENG-65");
    
    cout << "\n\nSample data loaded! Starting application...\n" << endl;
    
    
    library.run();
    
    return 0;
}