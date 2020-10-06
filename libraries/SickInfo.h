#pragma once

#include <iostream>

using std::string;

class Date {
public:
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;

    bool compare(Date &date) {
        bool result = false;

        if(date.year < year) {
            result = true;
        } else if(date.month < month) {
            result = true;
        } else if(date.day < day) {
            result = true;
        }

        return result;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Date &date) {
        stream << date.day << "/" << date.month << "/" << date.year;
        return stream;
    }
};

class FullName {
public:
    string name;
    string surname;
    string father_name;

    friend std::ostream &operator<<(std::ostream &stream, const FullName &name) {
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

    friend std::ostream &operator<<(std::ostream &stream, const SickInfo &info) {
        stream << info.full_name << " " << info.job << " " << info.number << " " << info.date << " " << info.incapacity_days << "\n";
        return stream;
    }
};