#include <iostream>
#include "libraries/SickInfo.h"

using std::cout;
using std::ifstream;

int main() {
    auto list = read_file_sick_list("files/input.txt");
    if(!list->is_empty()) {
        Date d;
        cout << "Введите день, месяц и год: ";
        d.console_set();
        clean_sick_list(list, d);

        if(print_file_sick_list("files/output.txt", list)) {
           cout << "Программа успешно завершена";
        } else {
            cout << "Не удалось записать в файл";
        }

    } else {
        cout << "Не удалось считать из файла";
    }

    delete list;
    return 0;
}
