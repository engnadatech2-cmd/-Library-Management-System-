#pragma once
#include <string>

struct Member {
    int         id;
    std::string name;
    std::string email;

    Member() : id(0), name(""), email("") {}
    Member(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email) {}

    void print() const;
};
