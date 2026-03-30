#pragma once
#include <string>

struct Book {
    int         id;
    std::string title;
    std::string author;
    bool        isAvailable;

    Book() : id(0), title(""), author(""), isAvailable(true) {}
    Book(int id, const std::string& title, const std::string& author)
        : id(id), title(title), author(author), isAvailable(true) {}

    void print() const;
};
