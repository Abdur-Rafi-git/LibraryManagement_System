#include "User.h"
#include <algorithm>

void User::displayUser() {
    cout << "\n--- User Information ---" << endl;
    cout << "User ID: " << userID << endl;
    cout << "User Name: " << userName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Department: " << department << endl;
    cout << "Registration Date: " << registrationDate << endl;
    cout << "Status: " << status << endl;
    cout << "Total Books Issued: " << totalBooksIssued << endl;
    cout << "Currently Issued Books: " << issuedBooks.size() << " book(s)" << endl;
    cout << "------------------------\n" << endl;
}

void User::addIssuedBook(int bookID) {
    issuedBooks.push_back(bookID);
    totalBooksIssued++;
}

void User::removeIssuedBook(int bookID) {
    auto it = find(issuedBooks.begin(), issuedBooks.end(), bookID);
    if (it != issuedBooks.end()) {
        issuedBooks.erase(it);
    }
}

int User::getIssuedBooksCount() {
    return issuedBooks.size();
}