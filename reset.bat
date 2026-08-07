@echo off
echo.
echo ============================================
echo    Library Management System - Data Reset
echo ============================================
echo.
echo Resetting data to original sample state...
echo.

REM Create books.csv
(
echo BookID,BookName,Author,Category,QuantityAvailable,IssueCount,AverageRating,TotalRatings
echo 101,The C++ Programming Language,Bjarne Stroustrup,Computer Science,5,20,4.5,18
echo 102,Grokking Algorithms,Aditya Bhargava,DSA,3,15,4.3,10
echo 103,Hamlet,William Shakespeare,English Literature,4,18,4.7,12
echo 104,Pather Panchali,Bibhutibhushan Bandyopadhyay,Bangla Literature,6,19,5.0,9
echo 105,The Cruel Birth of Bangladesh,Archer Blood,Bangladesh History,2,15,4.5,13
) > "data\books.csv"
echo [OK] books.csv reset

REM Create users.csv
(
echo UserID,UserName,PhoneNumber,Department,RegistrationDate,Status,TotalBooksIssued
echo 1001,Taseen,01712345678,CSE-56,01-07-2026,Active,10
echo 1002,Sadia,01987654321,CSE-56,02-07-2026,Active,8
echo 1003,Saon,01555555555,CSE-56,03-07-2026,Active,12
echo 1004,Cristiano,01666666666,ENG-64,04-07-2026,Active,9
echo 1005,Messi,01777777777,ENG-65,05-07-2026,Active,11
) > "data\users.csv"
echo [OK] users.csv reset

REM Create issues.csv
(
echo TransactionID,UserID,BookID,IssueDate,DueDate,ReturnDate,Status,FineAmount,RenewalCount
echo 5001,1001,101,06-07-2026,13-07-2026,12-07-2026,Returned,0,0
echo 5002,1002,102,08-07-2026,15-07-2026,15-07-2026,Returned,0,0
echo 5003,1003,103,13-07-2026,20-07-2026,(empty),Active,0,1
echo 5004,1004,104,09-07-2026,16-07-2026,17-07-2026,Returned,10,0
echo 5005,1005,105,11-07-2026,18-07-2026,(empty),Active,0,0
) > "data\issues.csv"
echo [OK] issues.csv reset

REM Create fines.csv
(
echo FineID,UserID,TransactionID,FineAmount,CalculationDate,PaymentStatus,PaymentDate
echo 999,1003,5003,10,21-07-2026,unpaid,(empty)
echo 1000,1004,5004,10,21-07-2026,paid,20-07-2026
echo 1001,1005,5005,30,21-07-2026,unpaid,(empty)
) > "data\fines.csv"
echo [OK] fines.csv reset

echo.
echo ============================================
echo All data reset to original sample state!
echo Ready for faculty demonstration.
echo ============================================
echo.
pause