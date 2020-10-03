#include <iostream>

#include "libraries/DList.h"

using std::cout;

int main() {
    auto list = new DList;

    list->add_to_head(1);
    list->add_to_head(2);
    list->add_to_head(3);
    list->print();

    list->add_to_tail(4);
    list->add_to_tail(5);
    list->add_to_tail(6);
    list->print();

    Node *n = list->get_node()->get_next()->get_next();
    list->remove(n);
    list->print();

    delete list;
    return 0;
}
