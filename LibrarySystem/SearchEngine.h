// SearchEngine — free functions only (STL allowed here per spec)
#pragma once

#include <string>
#include <algorithm>

#include "Book.h"
#include "LinkedList.h"

namespace SearchEngine {

// Convert string to lowercase (STL permitted inside SearchEngine)
inline std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

// O(n) linear scan — case-insensitive equality on title
inline Book* linearSearchByTitle(LinkedList<Book>& list,
                                  const std::string& title) {
    std::string target = toLower(title);
    for (auto* n = list.getHead(); n; n = n->next)
        if (toLower(n->data.title) == target)
            return &n->data;
    return nullptr;
}

// O(n) linear scan — case-insensitive equality on author
inline Book* linearSearchByAuthor(LinkedList<Book>& list,
                                   const std::string& author) {
    std::string target = toLower(author);
    for (auto* n = list.getHead(); n; n = n->next)
        if (toLower(n->data.author) == target)
            return &n->data;
    return nullptr;
}

} // namespace SearchEngine
