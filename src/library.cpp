#include "Library.h"
#include <algorithm>

Library::Library() {
    nextBookID = 101;
    nextUserID = 1001;
    nextTransactionID = 5001;
    nextFineID = 999;
}

// ===== BOOK MANAGEMENT =====

void Library::addBook(string name, string author, string category, int quantity) {
    Book newBook;
    newBook.setBookID(nextBookID);
    newBook.setBookName(name);
    newBook.setAuthor(author);
    newBook.setCategory(category);
    newBook.setQuantityAvailable(quantity);
    newBook.setIssueCount(0);
    newBook.setAverageRating(0.0);
    newBook.setTotalRatings(0);
    
    books.push_back(newBook);
    nextBookID++;
    
    cout << "\nBook added successfully! Book ID: " << newBook.getBookID() << endl;
}

Book* Library::searchBookByID(int bookID) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getBookID() == bookID) {
            return &books[i];
        }
    }
    return NULL;
}

Book* Library::searchBookByName(string name) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getBookName() == name) {
            return &books[i];
        }
    }
    return NULL;
}

void Library::displayAllBooks() {
    if (books.empty()) {
        cout << "\nNo books in library!" << endl;
        return;
    }
    
    cout << "\n========== ALL BOOKS IN LIBRARY ==========" << endl;
    for (int i = 0; i < books.size(); i++) {
        books[i].displayBook();
    }
}

void Library::editBook(int bookID, string name, string author, string category) {
    Book* book = searchBookByID(bookID);
    if (book != NULL) {
        book->setBookName(name);
        book->setAuthor(author);
        book->setCategory(category);
        cout << "\nBook updated successfully!" << endl;
    } else {
        cout << "\nBook not found!" << endl;
    }
}

void Library::deleteBook(int bookID) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getBookID() == bookID) {
            books.erase(books.begin() + i);
            cout << "\nBook deleted successfully!" << endl;
            return;
        }
    }
    cout << "\nBook not found!" << endl;
}

// ===== USER MANAGEMENT =====

void Library::registerUser(string name, string phone, string department) {
    User newUser;
    newUser.setUserID(nextUserID);
    newUser.setUserName(name);
    newUser.setPhoneNumber(phone);
    newUser.setDepartment(department);
    newUser.setRegistrationDate("01-01-2026");  // Default date
    newUser.setStatus("Active");
    newUser.setTotalBooksIssued(0);
    
    users.push_back(newUser);
    nextUserID++;
    
    cout << "\nUser registered successfully! User ID: " << newUser.getUserID() << endl;
}

User* Library::searchUserByID(int userID) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUserID() == userID) {
            return &users[i];
        }
    }
    return NULL;
}

User* Library::searchUserByName(string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUserName() == name) {
            return &users[i];
        }
    }
    return NULL;
}

void Library::displayAllUsers() {
    if (users.empty()) {
        cout << "\nNo users registered!" << endl;
        return;
    }
    
    cout << "\n========== ALL REGISTERED USERS ==========" << endl;
    for (int i = 0; i < users.size(); i++) {
        users[i].displayUser();
    }
}

void Library::updateUserStatus(int userID, string status) {
    User* user = searchUserByID(userID);
    if (user != NULL) {
        user->setStatus(status);
        cout << "\nUser status updated to: " << status << endl;
    } else {
        cout << "\nUser not found!" << endl;
    }
}

// ===== ISSUE MANAGEMENT =====

void Library::issueBook(int userID, int bookID, string issueDate) {
    User* user = searchUserByID(userID);
    Book* book = searchBookByID(bookID);
    
    if (user == NULL) {
        cout << "\nUser not found!" << endl;
        return;
    }
    
    if (book == NULL) {
        cout << "\nBook not found!" << endl;
        return;
    }
    
    if (book->getQuantityAvailable() <= 0) {
        cout << "\nBook not available!" << endl;
        return;
    }
    
    // Create new issue
    Issue newIssue;
    newIssue.setTransactionID(nextTransactionID);
    newIssue.setUserID(userID);
    newIssue.setBookID(bookID);
    newIssue.setStatus("Active");
    newIssue.calculateDueDate(issueDate);
    newIssue.setFineAmount(0);
    newIssue.setRenewalCount(0);
    
    issues.push_back(newIssue);
    
    // Update book quantity
    book->decreaseQuantity();
    book->increaseIssueCount();
    
    // Update user
    user->addIssuedBook(bookID);
    
    nextTransactionID++;
    
    cout << "\nBook issued successfully!" << endl;
    cout << "Transaction ID: " << newIssue.getTransactionID() << endl;
    cout << "Due Date: " << newIssue.getDueDate() << endl;
}

Issue* Library::searchIssueByTransactionID(int transactionID) {
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getTransactionID() == transactionID) {
            return &issues[i];
        }
    }
    return NULL;
}

void Library::displayActiveIssues() {
    cout << "\n========== ACTIVE ISSUES ==========" << endl;
    int count = 0;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStatus() == "Active") {
            issues[i].displayIssue();
            count++;
        }
    }
    if (count == 0) {
        cout << "\nNo active issues!" << endl;
    }
}

// ===== RETURN MANAGEMENT =====

void Library::returnBook(int transactionID, string returnDate) {
    Issue* issue = searchIssueByTransactionID(transactionID);
    
    if (issue == NULL) {
        cout << "\nTransaction not found!" << endl;
        return;
    }
    
    if (issue->getStatus() == "Returned") {
        cout << "\nBook already returned!" << endl;
        return;
    }
    
    // Calculate fine
    issue->calculateFine(returnDate);
    
    // Get book and update quantity
    Book* book = searchBookByID(issue->getBookID());
    if (book != NULL) {
        book->increaseQuantity();
    }
    
    // Get user and remove issued book
    User* user = searchUserByID(issue->getUserID());
    if (user != NULL) {
        user->removeIssuedBook(issue->getBookID());
    }
    
    // If there's a fine, record it
    if (issue->getFineAmount() > 0) {
        recordFine(issue->getUserID(), transactionID, issue->getFineAmount(), returnDate);
    }
    
    cout << "\nBook returned successfully!" << endl;
    if (issue->getFineAmount() > 0) {
        cout << "Fine Amount: " << issue->getFineAmount() << " Taka" << endl;
    }
}

// ===== RENEWAL MANAGEMENT =====

bool Library::renewBook(int transactionID) {
    Issue* issue = searchIssueByTransactionID(transactionID);
    
    if (issue == NULL) {
        cout << "\nTransaction not found!" << endl;
        return false;
    }
    
    if (issue->canRenew()) {
        issue->renewBook();
        cout << "\nBook renewed successfully!" << endl;
        cout << "New Due Date: " << issue->getDueDate() << endl;
        return true;
    } else {
        cout << "\nCannot renew this book!" << endl;
        cout << "Reason: Maximum renewals reached (2) or book is already returned" << endl;
        return false;
    }
}

// ===== RATING MANAGEMENT =====

void Library::rateBook(int bookID, float rating) {
    Book* book = searchBookByID(bookID);
    
    if (book == NULL) {
        cout << "\nBook not found!" << endl;
        return;
    }
    
    if (rating < 1.0 || rating > 5.0) {
        cout << "\nRating must be between 1.0 and 5.0!" << endl;
        return;
    }
    
    book->addRating(rating);
    cout << "\nRating added successfully!" << endl;
    cout << "New Average Rating: " << book->getAverageRating() << endl;
}

// ===== FINE MANAGEMENT =====

void Library::recordFine(int userID, int transactionID, float amount, string calcDate) {
    Fine newFine;
    newFine.setFineID(nextFineID);
    newFine.recordFine(userID, transactionID, amount, calcDate);
    
    fines.push_back(newFine);
    nextFineID++;
}

void Library::displayOutstandingFines() {
    cout << "\n========== OUTSTANDING FINES ==========" << endl;
    int count = 0;
    for (int i = 0; i < fines.size(); i++) {
        if (fines[i].getPaymentStatus() == "Unpaid") {
            fines[i].displayFine();
            count++;
        }
    }
    if (count == 0) {
        cout << "\nNo outstanding fines!" << endl;
    }
}

void Library::payFine(int fineID, string paymentDate) {
    for (int i = 0; i < fines.size(); i++) {
        if (fines[i].getFineID() == fineID) {
            fines[i].markAsPaid(paymentDate);
            cout << "\nFine paid successfully!" << endl;
            return;
        }
    }
    cout << "\nFine not found!" << endl;
}

// ===== REPORTS =====

void Library::displayTopBooksReport() {
    if (books.empty()) {
        cout << "\nNo books in library!" << endl;
        return;
    }
    
    cout << "\n========== TOP BOOKS REPORT ==========" << endl;
    cout << "Sorted by Issue Count (Most Borrowed):\n" << endl;
    
    vector<Book> sortedBooks = books;
    sort(sortedBooks.begin(), sortedBooks.end(), 
         [](const Book& a, const Book& b) {
             return a.getIssueCount() > b.getIssueCount();
         });
    
    for (int i = 0; i < sortedBooks.size() && i < 10; i++) {
        cout << (i + 1) << ". " << sortedBooks[i].getBookName() 
             << " - Issues: " << sortedBooks[i].getIssueCount() 
             << " - Rating: " << sortedBooks[i].getAverageRating() << endl;
    }
}

void Library::displayUserBorrowingHistory(int userID) {
    User* user = searchUserByID(userID);
    
    if (user == NULL) {
        cout << "\nUser not found!" << endl;
        return;
    }
    
    cout << "\n========== BORROWING HISTORY FOR: " << user->getUserName() << " ==========" << endl;
    
    int count = 0;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getUserID() == userID) {
            issues[i].displayIssue();
            count++;
        }
    }
    
    if (count == 0) {
        cout << "\nNo borrowing history!" << endl;
    }
}

// ===== DASHBOARD =====

void Library::displayNotificationDashboard(string todayDate) {
    cout << "\n========================================" << endl;
    cout << "    NOTIFICATION DASHBOARD" << endl;
    cout << "    Today: " << todayDate << endl;
    cout << "========================================\n" << endl;
    
    // Books due today
    cout << "[*] BOOKS DUE TODAY:\n" << endl;
    int count = 0;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStatus() == "Active" && issues[i].getDueDate() == todayDate) {
            User* user = searchUserByID(issues[i].getUserID());
            Book* book = searchBookByID(issues[i].getBookID());
            if (user != NULL && book != NULL) {
                cout << "  - Transaction " << issues[i].getTransactionID() << ": " 
                     << user->getUserName() << " - " << book->getBookName() << endl;
                count++;
            }
        }
    }
    if (count == 0) cout << "  (None)\n" << endl;
    else cout << endl;
    
    // Overdue books
    cout << "[*] OVERDUE BOOKS:\n" << endl;
    count = 0;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStatus() == "Active" && issues[i].isOverdue(todayDate)) {
            User* user = searchUserByID(issues[i].getUserID());
            Book* book = searchBookByID(issues[i].getBookID());
            if (user != NULL && book != NULL) {
                cout << "  - Transaction " << issues[i].getTransactionID() << ": " 
                     << user->getUserName() << " - " << book->getBookName() << endl;
                count++;
            }
        }
    }
    if (count == 0) cout << "  (None)\n" << endl;
    else cout << endl;
    
    // Users with pending fines
    cout << "[*] USERS WITH PENDING FINES:\n" << endl;
    count = 0;
    for (int i = 0; i < fines.size(); i++) {
        if (fines[i].getPaymentStatus() == "Unpaid") {
            User* user = searchUserByID(fines[i].getUserID());
            if (user != NULL) {
                cout << "  - " << user->getUserName() << ": " 
                     << fines[i].getFineAmount() << " Taka (Unpaid)" << endl;
                count++;
            }
        }
    }
    if (count == 0) cout << "  (None)\n" << endl;
    
    cout << "========================================\n" << endl;
}

// ===== MENU & RUN =====

void Library::displayMenu() {
    cout << "\n========================================" << endl;
    cout << "  LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Book Management" << endl;
    cout << "2. User Management" << endl;
    cout << "3. Issue Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. Book Renewal" << endl;
    cout << "6. View Notifications Dashboard" << endl;
    cout << "7. View Reports" << endl;
    cout << "8. Rate Book" << endl;
    cout << "9. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void Library::run() {
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            // Book Management Submenu
            int bookChoice;
            cout << "\n--- Book Management ---" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Search Book by ID" << endl;
            cout << "3. View All Books" << endl;
            cout << "4. Edit Book" << endl;
            cout << "5. Delete Book" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "Enter choice: ";
            cin >> bookChoice;
            cin.ignore();
            
            if (bookChoice == 1) {
                string name, author, category;
                int qty;
                cout << "Enter Book Name: ";
                getline(cin, name);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Category: ";
                getline(cin, category);
                cout << "Enter Quantity: ";
                cin >> qty;
                addBook(name, author, category, qty);
            } else if (bookChoice == 2) {
                int bookID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                Book* book = searchBookByID(bookID);
                if (book != NULL) {
                    book->displayBook();
                } else {
                    cout << "\nBook not found!" << endl;
                }
            } else if (bookChoice == 3) {
                displayAllBooks();
            } else if (bookChoice == 4) {
                int bookID;
                string name, author, category;
                cout << "Enter Book ID to edit: ";
                cin >> bookID;
                cin.ignore();
                cout << "Enter new Book Name: ";
                getline(cin, name);
                cout << "Enter new Author: ";
                getline(cin, author);
                cout << "Enter new Category: ";
                getline(cin, category);
                editBook(bookID, name, author, category);
            } else if (bookChoice == 5) {
                int bookID;
                cout << "Enter Book ID to delete: ";
                cin >> bookID;
                deleteBook(bookID);
            }
        } else if (choice == 2) {
            // User Management Submenu
            int userChoice;
            cout << "\n--- User Management ---" << endl;
            cout << "1. Register New User" << endl;
            cout << "2. Search User by ID" << endl;
            cout << "3. View All Users" << endl;
            cout << "4. Update User Status" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "Enter choice: ";
            cin >> userChoice;
            cin.ignore();
            
            if (userChoice == 1) {
                string name, phone, department;
                cout << "Enter User Name: ";
                getline(cin, name);
                cout << "Enter Phone Number: ";
                getline(cin, phone);
                cout << "Enter Department: ";
                getline(cin, department);
                registerUser(name, phone, department);
            } else if (userChoice == 2) {
                int userID;
                cout << "Enter User ID: ";
                cin >> userID;
                User* user = searchUserByID(userID);
                if (user != NULL) {
                    user->displayUser();
                } else {
                    cout << "\nUser not found!" << endl;
                }
            } else if (userChoice == 3) {
                displayAllUsers();
            } else if (userChoice == 4) {
                int userID;
                string status;
                cout << "Enter User ID: ";
                cin >> userID;
                cin.ignore();
                cout << "Enter Status (Active/Inactive): ";
                getline(cin, status);
                updateUserStatus(userID, status);
            }
        } else if (choice == 3) {
            int userID, bookID;
            string issueDate;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter Book ID: ";
            cin >> bookID;
            cin.ignore();
            cout << "Enter Issue Date (DD-MM-YYYY): ";
            getline(cin, issueDate);
            issueBook(userID, bookID, issueDate);
        } else if (choice == 4) {
            int transactionID;
            string returnDate;
            cout << "Enter Transaction ID: ";
            cin >> transactionID;
            cin.ignore();
            cout << "Enter Return Date (DD-MM-YYYY): ";
            getline(cin, returnDate);
            returnBook(transactionID, returnDate);
        } else if (choice == 5) {
            int transactionID;
            cout << "Enter Transaction ID to renew: ";
            cin >> transactionID;
            renewBook(transactionID);
        } else if (choice == 6) {
            string todayDate;
            cout << "Enter Today's Date (DD-MM-YYYY): ";
            cin.ignore();
            getline(cin, todayDate);
            displayNotificationDashboard(todayDate);
        } else if (choice == 7) {
            int reportChoice;
            cout << "\n--- Reports ---" << endl;
            cout << "1. Top Books Report" << endl;
            cout << "2. User Borrowing History" << endl;
            cout << "3. Outstanding Fines" << endl;
            cout << "4. Active Issues" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "Enter choice: ";
            cin >> reportChoice;
            
            if (reportChoice == 1) {
                displayTopBooksReport();
            } else if (reportChoice == 2) {
                int userID;
                cout << "Enter User ID: ";
                cin >> userID;
                displayUserBorrowingHistory(userID);
            } else if (reportChoice == 3) {
                displayOutstandingFines();
            } else if (reportChoice == 4) {
                displayActiveIssues();
            }
        } else if (choice == 8) {
            int bookID;
            float rating;
            cout << "Enter Book ID to rate: ";
            cin >> bookID;
            cout << "Enter Rating (1-5): ";
            cin >> rating;
            rateBook(bookID, rating);
        } else if (choice == 9) {
            cout << "\nThank you for using Library Management System!" << endl;
            running = false;
        } else {
            cout << "\nInvalid choice!" << endl;
        }
    }
}