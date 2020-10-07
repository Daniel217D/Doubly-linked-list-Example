#pragma once

#include <iostream>
#include <fstream>
#include "DList.h"

using std::cin;
using std::cout;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;

class Date {
public:
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;

    bool compare(Date &date) {
        return (date.year < year) ||
                (date.year == year && date.month < month) ||
                (date.year == year && date.month == month && date.day < day);
    }

    bool console_set() {
        cin >> day >> month >> year;
    }

    friend ostream &operator<<(ostream &stream, const Date &date) {
        stream << date.day << "/" << date.month << "/" << date.year;
        return stream;
    }
};

class FullName {
public:
    string name;
    string surname;
    string father_name;

    friend ostream &operator<<(ostream &stream, const FullName &name) {
        stream << name.surname << " " << name.name << " " << name.father_name;
        return stream;
    }
};

class SickInfo {
public:
    FullName full_name;
    string job;
    string number;
    Date date;
    unsigned short int incapacity_days;

    friend ostream &operator<<(ostream &stream, const SickInfo &info) {
        stream << info.full_name << " " << info.job << " " << info.number << " " << info.date << " " << info.incapacity_days << "\n";
        return stream;
    }
};

DList<SickInfo> *read_file_sick_list (const string& file_name) {
    auto list = new DList<SickInfo>;
    ifstream fin(file_name);

    if(fin.is_open()) {
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

        fin.close();
    }

    return list;
}

void clean_sick_list(DList<SickInfo> *list, Date date) {
    auto current = list->get_node();
    while (current && current->get_info().date.compare(date)) {
        list->remove(current);
        current = list->get_node();
    }
}

bool print_file_sick_list(const string& file_name, DList<SickInfo> *list) {
    ofstream fout(file_name);
    bool success = false;

    if(fout.is_open()) {
        auto current = list->get_node();

        while(current) {
            fout << current->get_info();
            current = current->get_next();
        }

        fout.close();
        success = true;
    }

    return success;
}
