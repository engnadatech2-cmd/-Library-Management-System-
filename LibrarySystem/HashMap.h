// HashMap<K,V> — open addressing, linear probing, capacity 101 (prime)
// hash(key) = key % CAPACITY
// K must support operator% and operator==
#pragma once

template<typename K, typename V>
class HashMap {
public:
    static constexpr int CAPACITY = 101;

private:
    enum class State { EMPTY, OCCUPIED, DELETED };

    struct Slot {
        K     key;
        V     value;
        State state;
        Slot() : key{}, value{}, state(State::EMPTY) {}
    };

    Slot slots_[CAPACITY];
    int  count_;

    int hash(const K& key) const { return key % CAPACITY; }

    // Linear probe: find slot for key (for insert)
    int probe(const K& key) {
        int idx = hash(key);
        int firstDeleted = -1;
        for (int i = 0; i < CAPACITY; ++i) {
            int cur = (idx + i) % CAPACITY;
            if (slots_[cur].state == State::OCCUPIED && slots_[cur].key == key)
                return cur;
            if (slots_[cur].state == State::DELETED && firstDeleted < 0)
                firstDeleted = cur;
            if (slots_[cur].state == State::EMPTY)
                return firstDeleted >= 0 ? firstDeleted : cur;
        }
        return firstDeleted >= 0 ? firstDeleted : idx;
    }

public:
    HashMap() : count_(0) {}

    // Insert or overwrite key → value
    void insert(const K& key, const V& value) {
        int idx = probe(key);
        if (slots_[idx].state != State::OCCUPIED) ++count_;
        slots_[idx].key   = key;
        slots_[idx].value = value;
        slots_[idx].state = State::OCCUPIED;
    }

    // O(1) average lookup; returns nullptr if not found
    V* get(const K& key) {
        int idx = hash(key);
        for (int i = 0; i < CAPACITY; ++i) {
            int cur = (idx + i) % CAPACITY;
            if (slots_[cur].state == State::EMPTY) break;
            if (slots_[cur].state == State::OCCUPIED && slots_[cur].key == key)
                return &slots_[cur].value;
        }
        return nullptr;
    }

    // Tombstone delete
    bool remove(const K& key) {
        int idx = hash(key);
        for (int i = 0; i < CAPACITY; ++i) {
            int cur = (idx + i) % CAPACITY;
            if (slots_[cur].state == State::EMPTY) break;
            if (slots_[cur].state == State::OCCUPIED && slots_[cur].key == key) {
                slots_[cur].state = State::DELETED; --count_; return true;
            }
        }
        return false;
    }

    // Iteration helpers (for FileHandler / printAllBooks)
    bool      isOccupied(int i)  const { return slots_[i].state == State::OCCUPIED; }
    V&        getValueAt(int i)        { return slots_[i].value; }
    const V&  getValueAt(int i)  const { return slots_[i].value; }
    int       size()             const { return count_; }
};
