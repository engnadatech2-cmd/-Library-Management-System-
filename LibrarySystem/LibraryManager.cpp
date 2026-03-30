#include "LibraryManager.h"
#include "FileHandler.h"
#include "SearchEngine.h"
#include <iostream>
#include <ctime>

// ── Constructor: load all data from CSV ───────────────────────
LibraryManager::LibraryManager()
    : nextBookId_(1), nextMemberId_(1), nextRecordId_(1)
{
    FileHandler::loadBooks  (bookMap_, bookList_, nextBookId_);
    FileHandler::loadMembers(members_, nextMemberId_);
    FileHandler::loadRecords(records_, nextRecordId_);
}

// ── Books ─────────────────────────────────────────────────────

void LibraryManager::addBook(const std::string& title,
                              const std::string& author) {
    Book b(nextBookId_++, title, author);
    bookMap_.insert(b.id, b);
    bookList_.add(b);
    FileHandler::saveBooks(bookMap_);
    std::cout << "Book added: [" << b.id << "] " << b.title << "\n";
}

void LibraryManager::removeBook(int id) {
    if (!bookMap_.get(id)) { std::cout << "Book not found.\n"; return; }
    bookMap_.remove(id);
    bookList_.removeById(id);
    FileHandler::saveBooks(bookMap_);
    std::cout << "Book [" << id << "] removed.\n";
}

void LibraryManager::searchBookById(int id) {
    Book* b = bookMap_.get(id);   // O(1)
    if (b) b->print(); else std::cout << "Book not found.\n";
}

void LibraryManager::searchBookByTitle(const std::string& title) {
    Book* b = SearchEngine::linearSearchByTitle(bookList_, title);
    if (b) b->print(); else std::cout << "Book not found.\n";
}

void LibraryManager::searchBookByAuthor(const std::string& author) {
    Book* b = SearchEngine::linearSearchByAuthor(bookList_, author);
    if (b) b->print(); else std::cout << "Book not found.\n";
}

// ── Members ───────────────────────────────────────────────────

void LibraryManager::addMember(const std::string& name,
                                const std::string& email) {
    Member m(nextMemberId_++, name, email);
    members_.add(m);
    FileHandler::saveMembers(members_);
    std::cout << "Member added: [" << m.id << "] " << m.name << "\n";
}

// ── Borrow / Return ───────────────────────────────────────────

void LibraryManager::borrowBook(int bookId, int memberId,
                                 const std::string& dueDate) {
    Book* b = bookMap_.get(bookId);
    if (!b || !b->isAvailable) { std::cout << "Book not available.\n"; return; }
    if (!members_.findById(memberId)) { std::cout << "Member not found.\n"; return; }
    b->isAvailable = false;
    Book* bl = bookList_.findById(bookId);  // keep list in sync
    if (bl) bl->isAvailable = false;
    BorrowRecord r(nextRecordId_++, bookId, memberId, currentDate(), dueDate);
    records_.add(r);
    FileHandler::saveBooks(bookMap_);
    FileHandler::saveRecords(records_);
    std::cout << "Borrowed. Record ID: " << r.id << "\n";
}

void LibraryManager::returnBook(int recordId) {
    BorrowRecord* r = records_.findById(recordId);
    if (!r || r->returned) { std::cout << "Record not found or already returned.\n"; return; }
    r->returned = true;
    Book* b = bookMap_.get(r->bookId);
    if (b) b->isAvailable = true;
    Book* bl = bookList_.findById(r->bookId);  // keep list in sync
    if (bl) bl->isAvailable = true;
    FileHandler::saveBooks(bookMap_);
    FileHandler::saveRecords(records_);
    std::cout << "Book returned. Thanks!\n";
}

// ── Display ───────────────────────────────────────────────────

void LibraryManager::printAllBooks() const {
    bool any = false;
    for (int i = 0; i < HashMap<int, Book>::CAPACITY; ++i)
        if (bookMap_.isOccupied(i)) { bookMap_.getValueAt(i).print(); any = true; }
    if (!any) std::cout << "No books in catalog.\n";
}

void LibraryManager::printAllMembers() const {
    members_.printAll();
    if (members_.size() == 0) std::cout << "No members.\n";
}

void LibraryManager::printActiveLoans() const {
    bool any = false;
    for (const auto* n = records_.getHead(); n; n = n->next)
        if (!n->data.returned) { n->data.print(); any = true; }
    if (!any) std::cout << "No active loans.\n";
}

void LibraryManager::printStats() const {
    int avail = 0;
    for (int i = 0; i < HashMap<int, Book>::CAPACITY; ++i)
        if (bookMap_.isOccupied(i) && bookMap_.getValueAt(i).isAvailable) ++avail;
    int active = 0;
    for (const auto* n = records_.getHead(); n; n = n->next)
        if (!n->data.returned) ++active;
    std::cout << "Books: "    << bookMap_.size()
              << " | Avail: " << avail
              << " | Members: " << members_.size()
              << " | Active Loans: " << active << "\n";
}

// ── Utility ───────────────────────────────────────────────────

std::string LibraryManager::currentDate() {
    time_t t  = time(nullptr);
    tm*    lt = localtime(&t);
    char buf[11];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d",
             lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
    return buf;
}
