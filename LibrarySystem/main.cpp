// Compile:
// g++ -std=c++17 main.cpp Book.cpp Member.cpp BorrowRecord.cpp
//     FileHandler.cpp LibraryManager.cpp -o library

#include <iostream>
#include <string>
#include <limits>
#include "LibraryManager.h"

static void printMenu() {
    std::cout << "\n=== Library Management System ===\n"
              << " 1.  Add Book\n"
              << " 2.  Remove Book\n"
              << " 3.  Search Book (by ID / Title / Author)\n"
              << " 4.  Add Member\n"
              << " 5.  Borrow Book\n"
              << " 6.  Return Book\n"
              << " 7.  View All Books\n"
              << " 8.  View All Members\n"
              << " 9.  View Active Loans\n"
              << " 10. Statistics\n"
              << " 0.  Exit\n"
              << "Choice: ";
}

static int readInt(const std::string& prompt = "") {
    if (!prompt.empty()) std::cout << prompt;
    int v;
    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number: ";
    }
    std::cin.ignore();
    return v;
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static void handleSearch(LibraryManager& lm) {
    std::cout << "Search by: 1) ID  2) Title  3) Author\nChoice: ";
    int c = readInt();
    if      (c == 1) lm.searchBookById(readInt("Book ID: "));
    else if (c == 2) lm.searchBookByTitle(readLine("Title: "));
    else if (c == 3) lm.searchBookByAuthor(readLine("Author: "));
    else             std::cout << "Invalid.\n";
}

static void handleBorrow(LibraryManager& lm) {
    int bid        = readInt("Book ID: ");
    int mid        = readInt("Member ID: ");
    std::string dd = readLine("Due date (YYYY-MM-DD): ");
    lm.borrowBook(bid, mid, dd);
}

static void dispatch(LibraryManager& lm, int choice) {
    switch (choice) {
        case 1:  lm.addBook(readLine("Title: "), readLine("Author: ")); break;
        case 2:  lm.removeBook(readInt("Book ID: "));                   break;
        case 3:  handleSearch(lm);                                       break;
        case 4:  lm.addMember(readLine("Name: "), readLine("Email: ")); break;
        case 5:  handleBorrow(lm);                                       break;
        case 6:  lm.returnBook(readInt("Record ID: "));                 break;
        case 7:  lm.printAllBooks();                                     break;
        case 8:  lm.printAllMembers();                                   break;
        case 9:  lm.printActiveLoans();                                  break;
        case 10: lm.printStats();                                        break;
        default: std::cout << "Invalid choice.\n";
    }
}

int main() {
    LibraryManager lm;
    int choice;
    do {
        printMenu();
        choice = readInt();
        if (choice != 0) dispatch(lm, choice);
    } while (choice != 0);
    std::cout << "Goodbye!\n";
    return 0;
}
