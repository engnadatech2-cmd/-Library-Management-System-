// LinkedList<T> — custom doubly linked list (header-only template)
// T must have a public int member named `id`.
#pragma once

template<typename T>
class LinkedList {
public:
    // Public node so FileHandler / SearchEngine can iterate
    struct Node {
        T     data;
        Node* next;
        Node* prev;
        explicit Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    LinkedList() : head_(nullptr), tail_(nullptr), count_(0) {}
    ~LinkedList() { clear(); }

    // Append item to the back
    void add(const T& item) {
        Node* n = new Node(item);
        if (!tail_) { head_ = tail_ = n; }
        else { n->prev = tail_; tail_->next = n; tail_ = n; }
        ++count_;
    }

    // Remove first node whose data.id == id
    bool removeById(int id) {
        for (Node* n = head_; n; n = n->next) {
            if (n->data.id == id) {
                unlink(n); delete n; --count_; return true;
            }
        }
        return false;
    }

    // Return pointer to data whose id matches, or nullptr
    T* findById(int id) {
        for (Node* n = head_; n; n = n->next)
            if (n->data.id == id) return &n->data;
        return nullptr;
    }

    // Call print() on every element
    void printAll() const {
        for (const Node* n = head_; n; n = n->next)
            n->data.print();
    }

    int          size()    const { return count_; }
    Node*        getHead()       { return head_; }
    const Node*  getHead() const { return head_; }

    void clear() {
        Node* cur = head_;
        while (cur) { Node* tmp = cur->next; delete cur; cur = tmp; }
        head_ = tail_ = nullptr; count_ = 0;
    }

private:
    Node* head_;
    Node* tail_;
    int   count_;

    void unlink(Node* n) {
        if (n->prev) n->prev->next = n->next; else head_ = n->next;
        if (n->next) n->next->prev = n->prev; else tail_ = n->prev;
    }
};
