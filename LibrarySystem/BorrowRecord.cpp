#include "BorrowRecord.h"
#include <iostream>

void BorrowRecord::print() const {
    std::cout << "Record[" << id << "]"
              << " Book:" << bookId
              << " Member:" << memberId
              << " Borrowed:" << borrowDate
              << " Due:" << dueDate
              << " [" << (returned ? "Returned" : "Active") << "]\n";
}
