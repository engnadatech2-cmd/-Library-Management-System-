# 📚 Library Management System — C++17

A fully functional console-based Library Management System built in C++17.  
Designed with clean OOP architecture, custom data structures, and full CSV persistence — no STL containers used in core logic.

---

## ✨ Features

- Add, remove, and search books (by ID, title, or author)
- Register members and manage borrow/return records
- Real-time availability tracking across all data structures
- Full CSV persistence — zero data loss between sessions
- Live statistics dashboard
- Case-insensitive search engine

---

## 🏗️ Architecture & Data Structures

| Component | Implementation | Complexity |
|-----------|---------------|------------|
| Book lookup by ID | `HashMap<int, Book>` — open addressing, linear probing | O(1) avg |
| Book search by title/author | `LinkedList<Book>` + `SearchEngine` | O(n) |
| Members & borrow records | `LinkedList<T>` — custom doubly linked | O(n) |
| File persistence | `FileHandler` — CSV read/write per entity | O(n) |

> All core data structures are custom-built — no `std::map`, `std::unordered_map`, or `std::list`.

---

## 📁 Project Structure

```
LibrarySystem/
├── main.cpp              # Entry point & menu loop
├── LibraryManager.cpp/h  # Core controller — orchestrates all operations
├── Book.cpp/h            # Book entity
├── Member.cpp/h          # Member entity
├── BorrowRecord.cpp/h    # Borrow/return record entity
├── HashMap.h             # Custom hash map (open addressing, capacity 101)
├── LinkedList.h          # Custom doubly linked list (header-only template)
├── SearchEngine.h        # Linear search by title & author
├── FileHandler.cpp/h     # CSV persistence layer
├── books.csv             # Auto-generated on first run
├── members.csv
└── records.csv
```

---

## ⚙️ Build & Run

```bash
g++ -std=c++17 main.cpp Book.cpp Member.cpp BorrowRecord.cpp FileHandler.cpp LibraryManager.cpp -o library
./library
```

> Requires: g++ with C++17 support

---

## 🖥️ Menu

```
=== Library Management System ===
 1.  Add Book
 2.  Remove Book
 3.  Search Book (by ID / Title / Author)
 4.  Add Member
 5.  Borrow Book
 6.  Return Book
 7.  View All Books
 8.  View All Members
 9.  View Active Loans
 10. Statistics
 0.  Exit
```

---

## 💾 Persistence

Each entity is stored in a separate CSV file, auto-created on first run:

| File | Contents |
|------|----------|
| `books.csv` | id, title, author, availability |
| `members.csv` | id, name, email |
| `records.csv` | id, bookId, memberId, borrowDate, dueDate, returned |

All data persists across sessions with zero data loss.

---

## 🔍 Design Highlights

- **Dual-structure sync** — `HashMap` for O(1) ID lookup, `LinkedList` for linear search; both stay in sync on every write operation
- **Tombstone deletion** — `HashMap` uses `DELETED` state to preserve probe chains
- **Template-based containers** — `LinkedList<T>` and `HashMap<K,V>` work with any type that exposes a public `int id`
- **Separation of concerns** — `FileHandler`, `SearchEngine`, and `LibraryManager` each own a single responsibility

---

## 🚀 Planned Features

- [ ] Due date overdue detection
- [ ] Member borrow history
- [ ] Multi-copy support per book title
- [ ] Mini Compiler (next project)

---

## 👩‍💻 Author

**Nada Magdy** — C++ Systems Developer  
[GitHub](https://github.com/engnadatech2-cmd) · [LinkedIn](https://linkedin.com/in/nada-magdy-6717703b9)
