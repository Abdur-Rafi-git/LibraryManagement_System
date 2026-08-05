#include "Fine.h"

void Fine::displayFine() {
    cout << "\n--- Fine Information ---" << endl;
    cout << "Fine ID: " << fineID << endl;
    cout << "User ID: " << userID << endl;
    cout << "Transaction ID: " << transactionID << endl;
    cout << "Fine Amount: " << fineAmount << " Taka" << endl;
    cout << "Calculation Date: " << calculationDate << endl;
    cout << "Payment Status: " << paymentStatus << endl;
    if (paymentStatus == "Paid") {
        cout << "Payment Date: " << paymentDate << endl;
    } else {
        cout << "Payment Date: (Not paid)" << endl;
    }
    cout << "------------------------\n" << endl;
}

void Fine::recordFine(int uid, int tid, float amount, string calcDate) {
    userID = uid;
    transactionID = tid;
    fineAmount = amount;
    calculationDate = calcDate;
    paymentStatus = "Unpaid";
    paymentDate = "";
}

void Fine::markAsPaid(string payDate) {
    paymentStatus = "Paid";
    paymentDate = payDate;
}

bool Fine::isPaid() {
    if (paymentStatus == "Paid") {
        return true;
    }
    return false;
}