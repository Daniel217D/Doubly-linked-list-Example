#include"DList.h"

#include<iostream>
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;

Node::Node(int _value, Node *_prev = nullptr, Node *_next = nullptr) : value(_value), prev(_prev), next(_next) {}

Node::~Node() {
    delete next;
}

Node *Node::get_next() {
    return next;
}

Node *Node::get_prev() {
    return prev;
}

int Node::get_value() {
    return value;
}

DList::~DList() {
    delete node;
}

Node *DList::get_node() {
    return node;
}

bool DList::is_empty() {
    return node == nullptr;
}

void DList::add_to_head(int value) {
    node = new Node(value, nullptr, node);

    if(node->next) {
        node->next->prev = node;
    }
}

void DList::add_to_tail(int value) {
    if (!is_empty()) {
        Node *current = node;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = new Node(value, current);
        current->next->prev = current;
    } else {
        add_to_head(value);
    }
}

void DList::add_after(Node *&after, int value) {
    if (after == nullptr) {
        return;
    }

    if (!is_empty()) {
        Node *current = node;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = new Node(value, current, current->next);

        if(current->next->next) {
            current->next->next->prev = current->next;
        }
    }
}

void DList::remove(Node *&del_el) {
    if (del_el == nullptr) {
        return;
    }

    if (node == del_el) {
        Node *temp = del_el->next;

        if (temp == nullptr) {
            delete node;
            node = nullptr;
        } else {
            del_el->next = nullptr;
            delete del_el;
            node = temp;
            node->prev = nullptr;
        }
    } else {
        Node *current = node;

        while (current && current->next != del_el) {
            current = current->next;
        }

        if (current != nullptr) {
            Node *temp = del_el->next;

            del_el->next = nullptr;
            del_el->prev = nullptr;
            delete del_el;

            current->next = temp;
            if(temp) {
                temp->prev = current;
            }
        }
    }
}

void DList::print() {
    Node *current = node;

    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }

    cout << "\n";
}