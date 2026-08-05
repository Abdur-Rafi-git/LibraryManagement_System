#ifndef FINE_H
#define FINE_H

#include <iostream>
#include <string>
using namespace std;

class Fine {
private:
    int fineID;
    int userID;
    int transactionID;
    float fineAmount;
    string calculationDate;
    string paymentStatus;  // "Unpaid" or "Paid"
    string paymentDate;

public:
    // Getters
    int getFineID() const { return fineID; }
    int getUserID() const { return userID; }
    int getTransactionID() const { return transactionID; }
    float getFineAmount() const { return fineAmount; }
    string getCalculationDate() const { return calculationDate; }
    string getPaymentStatus() const { return paymentStatus; }
    string getPaymentDate() const { return paymentDate; }
    
    // Setters
    void setFineID(int id) { fineID = id; }
    void setUserID(int uid) { userID = uid; }
    void setTransactionID(int tid) { transactionID = tid; }
    void setFineAmount(float amount) { fineAmount = amount; }
    void setCalculationDate(string date) { calculationDate = date; }
    void setPaymentStatus(string status) { paymentStatus = status; }
    void setPaymentDate(string date) { paymentDate = date; }
    
    // Methods
    void displayFine();
    void recordFine(int uid, int tid, float amount, string calcDate);
    void markAsPaid(string payDate);
    bool isPaid();
};

#endif