#pragma once

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "HashMap.h"
#include "LinkedList.h"

class FileHandler {
public:
    // Load books.csv → bookMap + bookList; updates nextId
    static void loadBooks(HashMap<int, Book>& map,
                          LinkedList<Book>&   list,
                          int& nextId);

    // Persist all books to books.csv
    static void saveBooks(const HashMap<int, Book>& map);

    // Load members.csv → members; updates nextId
    static void loadMembers(LinkedList<Member>& members, int& nextId);

    // Persist all members to members.csv
    static void saveMembers(const LinkedList<Member>& members);

    // Load records.csv → records; updates nextId
    static void loadRecords(LinkedList<BorrowRecord>& records, int& nextId);

    // Persist all borrow records to records.csv
    static void saveRecords(const LinkedList<BorrowRecord>& records);

private:
    static const char* BOOKS_FILE;
    static const char* MEMBERS_FILE;
    static const char* RECORDS_FILE;
};
