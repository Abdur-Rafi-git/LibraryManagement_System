#include "Issue.h"
#include <ctime>
#include <sstream>

void Issue::displayIssue() {
    cout << "\n--- Issue Information ---" << endl;
    cout << "Transaction ID: " << transactionID << endl;
    cout << "User ID: " << userID << endl;
    cout << "Book ID: " << bookID << endl;
    cout << "Issue Date: " << issueDate << endl;
    cout << "Due Date: " << dueDate << endl;
    if (status == "Returned") {
        cout << "Return Date: " << returnDate << endl;
    } else {
        cout << "Return Date: (Not returned)" << endl;
    }
    cout << "Status: " << status << endl;
    cout << "Fine Amount: " << fineAmount << " Taka" << endl;
    cout << "Renewal Count: " << renewalCount << " times" << endl;
    cout << "------------------------\n" << endl;
}

void Issue::calculateDueDate(string issDate) {
    issueDate = issDate;
    
    // Parse issue date (DD-MM-YYYY format)
    int day = stoi(issDate.substr(0, 2));
    int month = stoi(issDate.substr(3, 2));
    int year = stoi(issDate.substr(6, 4));
    
    // Add 7 days
    day += 7;
    
    // Handle month overflow
    if (day > 30) {
        day -= 30;
        month++;
    }
    
    if (month > 12) {
        month = 1;
        year++;
    }
    
    // Format due date
    char dueDateBuffer[11];
    sprintf(dueDateBuffer, "%02d-%02d-%04d", day, month, year);
    dueDate = dueDateBuffer;
}

void Issue::calculateFine(string retDate) {
    returnDate = retDate;
    status = "Returned";
    
    // Parse dates (DD-MM-YYYY format)
    int dueDay = stoi(dueDate.substr(0, 2));
    int dueMonth = stoi(dueDate.substr(3, 2));
    int dueYear = stoi(dueDate.substr(6, 4));
    
    int retDay = stoi(retDate.substr(0, 2));
    int retMonth = stoi(retDate.substr(3, 2));
    int retYear = stoi(retDate.substr(6, 4));
    
    // Simple calculation: convert to days since 01-01-2000
    int dueDays = dueYear * 365 + dueMonth * 30 + dueDay;
    int retDays = retYear * 365 + retMonth * 30 + retDay;
    
    int lateDays = retDays - dueDays;
    
    if (lateDays > 0) {
        fineAmount = lateDays * 10.0;  // 10 Taka per day
    } else {
        fineAmount = 0.0;  // No fine if on time
    }
}

bool Issue::canRenew() {
    // Can only renew if:
    // 1. Status is Active (not returned)
    // 2. Renewal count < 2 (max 2 renewals)
    // 3. Not already overdue

    //Bug  fix  5.4
    if (status != "Active") {
        return false;
    }
    
    if (renewalCount >= 2) {
        return false;
    }
    
    return true;

    /*
    if (status == "Active" && renewalCount < 2) {
        return true;
    }
    return false;
    */
}

void Issue::renewBook() {
    if (canRenew()) {
        // Parse due date
        int day = stoi(dueDate.substr(0, 2));
        int month = stoi(dueDate.substr(3, 2));
        int year = stoi(dueDate.substr(6, 4));
        
        // Add 7 more days
        day += 7;
        
        // Handle month overflow
        if (day > 30) {
            day -= 30;
            month++;
        }
        
        if (month > 12) {
            month = 1;
            year++;
        }
        
        // Update due date
        char newDueDateBuffer[11];
        sprintf(newDueDateBuffer, "%02d-%02d-%04d", day, month, year);
        dueDate = newDueDateBuffer;
        
        renewalCount++;
    }
}

bool Issue::isOverdue(string todayDate) {
    // Compare today's date with due date
    // If today > dueDate, it's overdue

    // notification bug 0.1
    if (todayDate.length() < 10 || dueDate.length() < 10) return false;
    
    int todayDay = stoi(todayDate.substr(0, 2));
    int todayMonth = stoi(todayDate.substr(3, 2));
    int todayYear = stoi(todayDate.substr(6, 4));
    
    int dueDay = stoi(dueDate.substr(0, 2));
    int dueMonth = stoi(dueDate.substr(3, 2));
    int dueYear = stoi(dueDate.substr(6, 4));

    // notification bug 1.0
    
    /*
    // Simple comparison
    if (todayYear > dueYear) return true;
    if (todayYear == dueYear && todayMonth > dueMonth) return true;
    if (todayYear == dueYear && todayMonth == dueMonth && todayDay > dueDay) return true;
    
    return false; */

    // Direct numerical comparison
    if (todayYear > dueYear) return true;
    if (todayYear < dueYear) return false;
    
    if (todayMonth > dueMonth) return true;
    if (todayMonth < dueMonth) return false;
    
    return todayDay > dueDay;
}