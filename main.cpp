#include <iostream>
#include <fstream>

#include "libraries/DList.h"
#include "libraries/SickInfo.h"

using std::cout;
using std::ifstream;

int main() {
    auto list = new DList<SickInfo>;

    ifstream fin("files/input.txt");

    while(!fin.eof()) {
        SickInfo temp;
        fin >> temp.full_name.surname;
        fin >> temp.full_name.name;
        fin >> temp.full_name.father_name;
        fin >> temp.job;
        fin >> temp.number;
        fin >> temp.date.day;
        fin >> temp.date.month;
        fin >> temp.date.year;
        fin >> temp.incapacity_days;


        if(list->is_empty() || !list->get_node()->get_info().date.compare(temp.date)) {
            list->add_to_head(temp);
        } else {
            auto current = list->get_node();
            while (current->get_next() != nullptr && current->get_next()->get_info().date.compare(temp.date)) {
                current = current->get_next();
            }
            list->add_after(current, temp);
        }

    }

    list->print();

    delete list;
    return 0;
}
