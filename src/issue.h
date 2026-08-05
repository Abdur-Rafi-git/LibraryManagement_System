#ifndef ISSUE_H
#define ISSUE_H

#include<bits/stdc++.h>
using namespace std;

class Issue {
private:
    int transactionID;
    int userID;
    int bookID;
    string issueDate;
    string dueDate;
    string returnDate;
    string status;  // "Active" or "Returned"
    float fineAmount;
    int renewalCount;  // Track renewals (max 2)

public:
    // Getters
    int getTransactionID()  const { return transactionID; }
    int getUserID()  const { return userID; }
    int getBookID()  const { return bookID; }
    string getIssueDate()  const { return issueDate; }
    string getDueDate()  const { return dueDate; }
    string getReturnDate()  const { return returnDate; }
    string getStatus() const  { return status; }
    float getFineAmount()  const { return fineAmount; }
    int getRenewalCount()  const { return renewalCount; }
    
    // Setters
    void setTransactionID(int id) { transactionID = id; }
    void setUserID(int uid) { userID = uid; }
    void setBookID(int bid) { bookID = bid; }
    void setIssueDate(string date) { issueDate = date; }
    void setDueDate(string date) { dueDate = date; }
    void setReturnDate(string date) { returnDate = date; }
    void setStatus(string s) { status = s; }
    void setFineAmount(float amount) { fineAmount = amount; }
    void setRenewalCount(int count) { renewalCount = count; }
    
    // Methods
    void displayIssue();
    void calculateDueDate(string issueDate);  // Add 7 days
    void calculateFine(string returnDate);    // 10 Taka per day late
    bool canRenew();                          // Check if can renew (max 2 times)
    void renewBook();                         // Extend due date by 7 days
    bool isOverdue(string todayDate);        // Check if overdue
};

#endif