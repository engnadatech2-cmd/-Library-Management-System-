#pragma once
#include <string>

struct BorrowRecord {
    int         id;        // recordId per spec
    int         bookId;
    int         memberId;
    std::string borrowDate;
    std::string dueDate;
    bool        returned;

    BorrowRecord() : id(0), bookId(0), memberId(0), returned(false) {}
    BorrowRecord(int rid, int bid, int mid,
                 const std::string& bd, const std::string& dd)
        : id(rid), bookId(bid), memberId(mid),
          borrowDate(bd), dueDate(dd), returned(false) {}

    void print() const;
};
