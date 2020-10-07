#pragma once

#include <iostream>

using std::cout;
using std::string;

template<class Type>
class Node {
private:
    Type info;

    Node<Type> *next;

    Node<Type> *prev;

    template<typename> friend class DList;

public:
    explicit Node(Type _info, Node<Type> *_prev, Node<Type> *_next) : info(_info), prev(_prev), next(_next) {
    }

    ~Node() {
        delete next;
    }

    Node<Type> *get_next() {
        return next;
    };

    Node<Type> *get_prev() {
        return prev;
    }

    Type get_info() {
        return info;
    }
};

template<class Type>
class DList {
private:
    Node<Type> *node = nullptr;

public:
    ~DList() {
        delete node;
    }

    Node<Type> *get_node() {
        return node;
    }

    bool is_empty() {
        return node == nullptr;
    }

    void add_to_head(Type info) {
        node = new Node<Type>(info, nullptr, node);

        if (node->next) {
            node->next->prev = node;
        }
    }

    void add_to_tail(Type info) {
        if (!is_empty()) {
            Node<Type> *current = node;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = new Node<Type>(info, current, nullptr);
            current->next->prev = current;
        } else {
            add_to_head(info);
        }
    }

    void add_after(Node<Type> *&after, Type info) {
        if (after == nullptr) {
            return;
        }

        if (!is_empty()) {
            after->next = new Node<Type>(info, after, after->next);

            if (after->next->next) {
                after->next->next->prev = after->next;
            }
        }
    }

    void remove(Node<Type> *&del_el) {
        if (del_el == nullptr) {
            return;
        }

        if (del_el->prev == nullptr) {
            Node<Type> *temp = del_el->next;

            if (temp == nullptr) {
                delete del_el;
                node = nullptr;
            } else {
                del_el->next = nullptr;
                delete del_el;
                node = temp;
                node->prev = nullptr;
            }
        } else {
            Node<Type> *next = del_el->next;
            Node<Type> *prev = del_el->prev;

            del_el->next = nullptr;
            del_el->prev = nullptr;
            delete del_el;

            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
    }

    void print() {
        Node<Type> *current = node;

        while (current != nullptr) {
            cout << current->info << " ";
            current = current->next;
        }

        cout << "\n";
    }
};