#include "Book.h"
#include <iostream>

void Book::print() const {
    std::cout << "[" << id << "] " << title
              << " by " << author
              << " [" << (isAvailable ? "Available" : "Borrowed") << "]\n";
}
