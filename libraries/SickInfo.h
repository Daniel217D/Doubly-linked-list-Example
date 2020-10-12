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
private:
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;

    bool compare(Date &date) {
        return (date.year < year) ||
               (date.year == year && date.month < month) ||
               (date.year == year && date.month == month && date.day < day);
    }

    friend class SickInfo;

public:
    bool console_set() {
        cin >> day >> month >> year;
    }

    friend ostream &operator<<(ostream &stream, const Date &date) {
        stream << date.day << "/" << date.month << "/" << date.year;
        return stream;
    }
};

class FullName {
private:
    string name;
    string surname;
    string father_name;

    friend class SickInfo;

public:
    friend ostream &operator<<(ostream &stream, const FullName &name) {
        stream << name.surname << " " << name.name << " " << name.father_name;
        return stream;
    }
};

class SickInfo {
private:
    FullName full_name;
    string job;
    string number;
    Date date;
    unsigned short int incapacity_days;
public:
    SickInfo(ifstream &fin) {
        fin >> full_name.surname;
        fin >> full_name.name;
        fin >> full_name.father_name;
        fin >> job;
        fin >> number;
        fin >> date.day;
        fin >> date.month;
        fin >> date.year;
        fin >> incapacity_days;
    }

    bool compare(SickInfo &info) {
        return date.compare(info.date);
    }

    bool compare(Date &_date) {
        return date.compare(_date);
    }

    friend ostream &operator<<(ostream &stream, const SickInfo &info) {
        stream << info.full_name << " " << info.job << " " << info.number << " " << info.date << " "
               << info.incapacity_days << "\n";
        return stream;
    }
};

DList<SickInfo> *read_file_sick_list(const string &file_name) {
    auto list = new DList<SickInfo>;
    ifstream fin(file_name);

    if (fin.is_open()) {
        while (!fin.eof()) {
            SickInfo temp(fin);
            list->add_to_tail(temp);
        }

        fin.close();
    }

    return list;
}

void clean_sick_list(DList<SickInfo> *list, Date date) {
    auto current = list->get_node();
    while (current && current->get_info().compare(date)) {
        list->remove(current);
        current = list->get_node();
    }
}

bool print_file_sick_list(const string &file_name, DList<SickInfo> *list) {
    ofstream fout(file_name);
    bool success = false;

    if (fout.is_open()) {
        auto current = list->get_node();

        while (current) {
            fout << current->get_info();
            current = current->get_next();
        }

        fout.close();
        success = true;
    }

    return success;
}
