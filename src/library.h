#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Issue.h"
#include "Fine.h"
using namespace std;

class Library {
private:
    vector<Book> books;
    vector<User> users;
    vector<Issue> issues;
    vector<Fine> fines;
    
    int nextBookID;
    int nextUserID;
    int nextTransactionID;
    int nextFineID;

public:
    Library();
    
    // Book Management
    void addBook(string name, string author, string category, int quantity);
    Book* searchBookByID(int bookID);
    Book* searchBookByName(string name);
    void displayAllBooks();
    void editBook(int bookID, string name, string author, string category);
    void deleteBook(int bookID);
    
    // User Management
    void registerUser(string name, string phone, string department);
    User* searchUserByID(int userID);
    User* searchUserByName(string name);
    void displayAllUsers();
    void updateUserStatus(int userID, string status);
    
    // Issue Management
    void issueBook(int userID, int bookID, string issueDate);
    Issue* searchIssueByTransactionID(int transactionID);
    void displayActiveIssues();
    
    // Return Management
    void returnBook(int transactionID, string returnDate);
    
    // Renewal Management
    bool renewBook(int transactionID);
    
    // Rating Management
    void rateBook(int bookID, float rating);
    
    // Fine Management
    void recordFine(int userID, int transactionID, float amount, string calcDate);
    void displayOutstandingFines();
    void payFine(int fineID, string paymentDate);
    
    // Reports
    void displayTopBooksReport();
    void displayUserBorrowingHistory(int userID);
    
    // Dashboard
    void displayNotificationDashboard(string todayDate);
    
    // Utility
    void displayMenu();
    void run();

    // File I/O Functions
    void loadAllData();
    void saveAllData();
    void loadBooksFromFile();
    void saveBooksToFile();
    void loadUsersFromFile();
    void saveUsersToFile();
    void loadIssuesFromFile();
    void saveIssuesToFile();
    void loadFinesFromFile();
    void saveFinestoFile();
};

#endif