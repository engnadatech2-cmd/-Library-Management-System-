#pragma once

#include <string>
#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "HashMap.h"
#include "LinkedList.h"

class LibraryManager {
public:
    LibraryManager();

    void addBook(const std::string& title, const std::string& author);
    void removeBook(int id);
    void searchBookById(int id);
    void searchBookByTitle(const std::string& title);
    void searchBookByAuthor(const std::string& author);

    void addMember(const std::string& name, const std::string& email);

    void borrowBook(int bookId, int memberId, const std::string& dueDate);
    void returnBook(int recordId);

    void printAllBooks()   const;
    void printAllMembers() const;
    void printActiveLoans() const;
    void printStats()      const;

private:
    HashMap<int, Book>       bookMap_;   // O(1) lookup by id
    LinkedList<Book>         bookList_;  // for title/author search
    LinkedList<Member>       members_;
    LinkedList<BorrowRecord> records_;

    int nextBookId_;
    int nextMemberId_;
    int nextRecordId_;

    static std::string currentDate();
};
