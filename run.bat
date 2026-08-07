@echo off
cd /d "%~dp0src"
echo Compiling Library Management System...
echo.
g++ -o library main.cpp Book.cpp user.cpp issue.cpp fine.cpp library.cpp -std=c++11
if %errorlevel% equ 0 (
    echo.
    echo  Compilation successful!
    echo.
    echo Starting program...
    echo.
    library.exe
) else (
    echo.
    echo  Compilation FAILED! Check errors above.
    echo.
)
pause