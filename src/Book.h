#ifndef BOOK_H
#define BOOK_H
#include<bits/stdc++.h>
using namespace std;

class Book{
private:
    int bookID;
    string bookName;
    string author;
    string category;
    int quantityAvailable;
    int issueCount;
    float averageRating;
    int  totalRatings;

public:
    //Getters
    int getBookID() const  {return bookID; }
    string getBookName() const {return bookName;}
    string getAuthor() const {return author;}
    string getCategory() const  {return category;}
    int getQuantityAvailable() const {return quantityAvailable;}
    int getIssueCount() const {return issueCount;}
    int getAverageRating() const  {return averageRating;}
    int getTotalRatings() const {return totalRatings;}

    //setters
    void setBookID(int id) {bookID = id; }
    void setBookName( string name) {bookName = name; }
    void setAuthor( string a ){author = a ;}
    void setCategory(string cat) {category =  cat;}
    void setQuantityAvailable( int qty) {quantityAvailable = qty;}
    void setIssueCount(int count) {issueCount = count;}
    void setAverageRating( float rating) {averageRating = rating;}
    void setTotalRatings(int ratings) {totalRatings = ratings;}

    //Methods
    void displayBook();
    void increaseIssueCount();
    void decreaseQuantity();
    void increaseQuantity();
    void addRating(float rating);

};

#endif