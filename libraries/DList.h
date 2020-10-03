#pragma once

#include <iostream>

using std::string;

class Node {
private:
    int value;

    Node *next;

    Node *prev;

    friend class DList;

public:
    explicit Node(int _value, Node *_prev, Node *_next);

    ~Node();

    Node *get_next();

    Node *get_prev();

    int get_value();
};

class DList {
private:
    Node *node = nullptr;

public:
    ~DList();

    Node *get_node();

    bool is_empty();

    void add_to_head(int value);

    void add_to_tail(int value);

    void add_after(Node *&after, int value);

    void remove(Node *&del_el);

    void print();
};
