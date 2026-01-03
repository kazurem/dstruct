#pragma once
#include "node.hpp"

template <typename T>
class SCLList {
  public:
    SCLList(SNode<T> *head = nullptr);

    // Accessors
    int size() const;
    int count(T val) const;
    void display(bool debug = false) const;

    // Mutators
    void insert(int idx, T val);
    void pop(int idx);
    int erase(T val);

  private:
    SNode<T> *_head;
    SNode<T> *head() const;
    SNode<T> *tail() const;
    void head(SNode<T> *ptr);
};

template <typename T>
SCLList<T>::SCLList(SNode<T> *head) : _head(head) { }

// Accessors
template <typename T>
int SCLList<T>::size() const {
    if (!head()) return 0;
    int       size    = 0;
    SNode<T> *tmp_ptr = head();
    do {
        size++;
        tmp_ptr = tmp_ptr->nptr();
    } while (tmp_ptr != head());
    return size;
};
template <typename T>
int SCLList<T>::count(T val) const {
    int       count   = 0;
    SNode<T> *tmp_ptr = head();
    while (tmp_ptr->nptr() != head()) {
        if (tmp_ptr->val() == val) count++;
        tmp_ptr = tmp_ptr->nptr();
    }
    return count;
};
template <typename T>
void SCLList<T>::display(bool debug) const {
    if (!head()) {
        std::cout << "{}";
        return;
    }
    std::cout << "{";
    SNode<T> *tmp_ptr = head();
    do {
        if (debug) {
            std::cout << "\n" << tmp_ptr << ",";
        }
        std::cout << tmp_ptr->val() << ",";
        if (debug) {
            std::cout << tmp_ptr->nptr() << ",\n";
        }
        tmp_ptr = tmp_ptr->nptr();
    } while (tmp_ptr != head());
    std::cout << "}";
};

// Mutators
template <typename T>
void SCLList<T>::insert(int idx, T val) {
    SNode<T> *new_node = new SNode<T>(val);

    if (idx == 0) {
        if (!head()) {
            head(new_node);
            new_node->nptr(new_node);
        } else {
            new_node->nptr(head());
            tail()->nptr(new_node);
            head(new_node);
        }
    } else if (idx > 0) {
        int       idx_count = 0;
        SNode<T> *tmp_ptr   = head();

        while (idx_count < idx - 1 && tmp_ptr->nptr() != head()) {
            idx_count++;
            tmp_ptr = tmp_ptr->nptr();
        }

        new_node->nptr(tmp_ptr->nptr());
        tmp_ptr->nptr(new_node);
    }
};
template <typename T>
void SCLList<T>::pop(int idx) {
    if (!head()) {
        throw std::underflow_error("Trying to delete from empty list");
    }

    SNode<T> *tmp_ptr = head();
    if (idx == 0) {
        if (head()->nptr() == head()) {
            head(nullptr);
        } else {
            tail()->nptr(head()->nptr());
            head(head()->nptr());
        }
        delete tmp_ptr;
        tmp_ptr = nullptr;
    } else if (idx > 0 && idx < size()) {
        int idx_count = 0;
        while (idx_count < idx - 1) {
            idx_count++;
            tmp_ptr = tmp_ptr->nptr();
        }

        SNode<T> *anthr_tmp_ptr = tmp_ptr->nptr();
        tmp_ptr->nptr(anthr_tmp_ptr->nptr());
        delete anthr_tmp_ptr;
    }
};
template <typename T>
int SCLList<T>::erase(T val) {
    if (!head()) return 0;

    int       count   = 0;
    SNode<T> *prev    = head();
    SNode<T> *current = head()->nptr();

    do {
        if (current->val() == val) {
            SNode<T> *temp = current;
            count++;
            prev->nptr(current->nptr());
            current = prev->nptr();

            delete temp;
            temp = nullptr;

        } else {
            prev    = current;
            current = current->nptr();
        }
    } while (current != head() && head());

    if (head()->val() == val) pop(0);

    return count;
};

template <typename T>
SNode<T> *SCLList<T>::head() const {
    return _head;
}
template <typename T>
void SCLList<T>::head(SNode<T> *ptr) {
    _head = ptr;
}
template <typename T>
SNode<T> *SCLList<T>::tail() const {
    if (!head()) return nullptr;
    SNode<T> *tmp_ptr = head();
    while (tmp_ptr->nptr() != head())
        tmp_ptr = tmp_ptr->nptr();
    return tmp_ptr;
}
