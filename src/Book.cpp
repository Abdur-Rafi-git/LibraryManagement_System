#include "Book.h"

void Book::displayBook() {
    cout << "\n--- Book Information ---" << endl;
    cout << "Book ID: " << bookID << endl;
    cout << "Book Name: " << bookName << endl;
    cout << "Author: " << author << endl;
    cout << "Category: " << category << endl;
    cout << "Quantity Available: " << quantityAvailable << endl;
    cout << "Issue Count: " << issueCount << endl;
    cout << "Average Rating: " << averageRating << " (" << totalRatings << " ratings)" << endl;
    cout << "------------------------\n" << endl;
}

void Book::increaseIssueCount() {
    issueCount++;
}

void Book::decreaseQuantity() {
    if (quantityAvailable > 0) {
        quantityAvailable--;
    }
}

void Book::increaseQuantity() {
    quantityAvailable++;
}

void Book::addRating(float rating) {
    if (rating >= 1.0 && rating <= 5.0) {
        averageRating = (averageRating * totalRatings + rating) / (totalRatings + 1);
        totalRatings++;
    }
}