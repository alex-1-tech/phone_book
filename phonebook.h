#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class PhoneBook : public QWidget {
Q_OBJECT

public:
    explicit PhoneBook();

private
    slots:

    void addContact();

    void deleteContact();

    void loadContacts();

private:
    QLineEdit *name;
    QLineEdit *phone;
    QListWidget *contacts;
};
