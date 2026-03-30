#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <string>

const char* FileHandler::BOOKS_FILE   = "books.csv";
const char* FileHandler::MEMBERS_FILE = "members.csv";
const char* FileHandler::RECORDS_FILE = "records.csv";

// ── Books ─────────────────────────────────────────────────────

void FileHandler::saveBooks(const HashMap<int, Book>& map) {
    std::ofstream f(BOOKS_FILE);
    for (int i = 0; i < HashMap<int, Book>::CAPACITY; ++i) {
        if (!map.isOccupied(i)) continue;
        const Book& b = map.getValueAt(i);
        f << b.id << "," << b.title << ","
          << b.author << "," << b.isAvailable << "\n";
    }
}

void FileHandler::loadBooks(HashMap<int, Book>& map,
                             LinkedList<Book>&   list,
                             int& nextId) {
    std::ifstream f(BOOKS_FILE);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        Book b;
        std::getline(ss, tok,      ','); b.id          = std::stoi(tok);
        std::getline(ss, b.title,  ',');
        std::getline(ss, b.author, ',');
        std::getline(ss, tok,      ','); b.isAvailable = (tok == "1");
        map.insert(b.id, b);
        list.add(b);
        if (b.id >= nextId) nextId = b.id + 1;
    }
}

// ── Members ───────────────────────────────────────────────────

void FileHandler::saveMembers(const LinkedList<Member>& members) {
    std::ofstream f(MEMBERS_FILE);
    for (const auto* n = members.getHead(); n; n = n->next)
        f << n->data.id << "," << n->data.name << "," << n->data.email << "\n";
}

void FileHandler::loadMembers(LinkedList<Member>& members, int& nextId) {
    std::ifstream f(MEMBERS_FILE);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        Member m;
        std::getline(ss, tok,      ','); m.id = std::stoi(tok);
        std::getline(ss, m.name,   ',');
        std::getline(ss, m.email,  ',');
        members.add(m);
        if (m.id >= nextId) nextId = m.id + 1;
    }
}

// ── Borrow Records ────────────────────────────────────────────

void FileHandler::saveRecords(const LinkedList<BorrowRecord>& records) {
    std::ofstream f(RECORDS_FILE);
    for (const auto* n = records.getHead(); n; n = n->next) {
        const BorrowRecord& r = n->data;
        f << r.id       << "," << r.bookId   << "," << r.memberId   << ","
          << r.borrowDate << "," << r.dueDate << "," << r.returned  << "\n";
    }
}

void FileHandler::loadRecords(LinkedList<BorrowRecord>& records, int& nextId) {
    std::ifstream f(RECORDS_FILE);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        BorrowRecord r;
        std::getline(ss, tok,          ','); r.id       = std::stoi(tok);
        std::getline(ss, tok,          ','); r.bookId   = std::stoi(tok);
        std::getline(ss, tok,          ','); r.memberId = std::stoi(tok);
        std::getline(ss, r.borrowDate, ',');
        std::getline(ss, r.dueDate,    ',');
        std::getline(ss, tok,          ','); r.returned = (tok == "1");
        records.add(r);
        if (r.id >= nextId) nextId = r.id + 1;
    }
}
