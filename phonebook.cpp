#include "phonebook.h"


PhoneBook::PhoneBook() : QWidget(nullptr) {
    // qDebug()  <<  QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("phonebook.db");
    db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE "
               "IF NOT EXISTS contacts "
               "(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, phone TEXT)");
    auto *layout = new QVBoxLayout(this);

    name = new QLineEdit(this);
    name->setPlaceholderText("Input name: ");
    layout->addWidget(name);

    phone = new QLineEdit(this);
    phone->setPlaceholderText("Введите телефон");
    layout->addWidget(phone);

    auto *addButton = new QPushButton("Добавить контакт", this);
    layout->addWidget(addButton);

    contacts = new QListWidget(this);
    layout->addWidget(contacts);

    auto *deleteButton = new QPushButton("Удалить контакт", this);
    layout->addWidget(deleteButton);

    connect(addButton, &QPushButton::clicked, this, &PhoneBook::addContact);
    connect(deleteButton, &QPushButton::clicked, this, &PhoneBook::deleteContact);

    loadContacts();
}

void PhoneBook::addContact() {
    QString input_name = name->text();
    QString input_phone = phone->text();

    if (input_name.isEmpty() || input_phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "The name and phone number cannot be empty!");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, phone) VALUES (:name, :phone)");
    query.bindValue(":name", input_name);
    query.bindValue(":phone", input_phone);
    query.exec();

    name->clear();
    phone->clear();
    loadContacts();
}

void PhoneBook::deleteContact() {
    QListWidgetItem *selectedItem = contacts->currentItem();
    if (selectedItem) {
        QStringList contactDetails = selectedItem->text().split(" - ");
        QString input_name = contactDetails[0];

        QSqlQuery query;
        query.prepare("DELETE FROM contacts WHERE name = :name");
        query.bindValue(":name", input_name);
        query.exec();

        loadContacts();
    } else {
        QMessageBox::warning(this, "Error", "Select the contact to delete!");
    }
}

void PhoneBook::loadContacts() {
    contacts->clear();
    QSqlQuery query("SELECT name, phone FROM contacts");
    while (query.next()) {
        QString input_name = query.value(0).toString();
        QString input_phone = query.value(1).toString();
        contacts->addItem(input_name + " - " + input_phone);
    }
}
