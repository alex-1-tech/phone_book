#include "phonebook.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PhoneBook phoneBook;
    phoneBook.setWindowTitle("Телефонная книга");
    phoneBook.resize(400, 300);
    phoneBook.show();
    return QApplication::exec();
}