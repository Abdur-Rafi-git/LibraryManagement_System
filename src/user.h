#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
using namespace std;

class User {
private:
    int userID;
    string userName;
    string phoneNumber;
    string department;
    string registrationDate;
    string status;
    vector<int> issuedBooks;
    int totalBooksIssued;

public:
    // Getters
    int getUserID() const { return userID; }
    string getUserName() const { return userName; }
    string getPhoneNumber() const { return phoneNumber; }
    string getDepartment() const { return department; }
    string getRegistrationDate() const { return registrationDate; }
    string getStatus() const { return status; }
    int getTotalBooksIssued() const { return totalBooksIssued; }
    vector<int> getIssuedBooks() const { return issuedBooks; }
    
    // Setters
    void setUserID(int id) { userID = id; }
    void setUserName(string name) { userName = name; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    void setDepartment(string dept) { department = dept; }
    void setRegistrationDate(string date) { registrationDate = date; }
    void setStatus(string s) { status = s; }
    void setTotalBooksIssued(int total) { totalBooksIssued = total; }
    
    // Methods
    void displayUser();
    void addIssuedBook(int bookID);
    void removeIssuedBook(int bookID);
    int getIssuedBooksCount();
};

#endif