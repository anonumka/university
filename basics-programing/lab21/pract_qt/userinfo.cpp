#include "userinfo.hpp"
#include <QTextStream>

userinfo::userinfo()
{
    this->surname = "UNDEFINDED";
    this->login = "UNDEFINDED";
    this->password = "UNDEFINDED";
    this->access = false;
}

bool userinfo::access_read(QTextStream& ist)
{
    QString tmp;
    tmp = ist.readLine();
    if (tmp == " \"Доступ есть\"")
        return 1;
    else
        return 0;
}

void userinfo::load_txt(QTextStream& ist)
{
    ist >> surname;
    ist >> login;
    ist >> password;
    access = access_read(ist);
}

//void user::save_bin_string(const QString& name, QDataStream& ost) const
//{
//    QChar tmp;
//    size_t len = name.size();
//    ost.writeBytes((char*)(&len), sizeof(size_t));
//    for (size_t i = 0; i < len; i++)
//    {
//        tmp = name[i];
//        ost.writeBytes((char*)(&tmp), sizeof(QChar));
//    }
//}

void userinfo::save_bin(QDataStream& ost) const
{
    ost << surname;
    ost << login;
    ost << password;
    ost << access;
}

//void user::load_bin_string(QString& name, QDataStream& ist)
//{
//    size_t len = 0; QChar tmp;
//    ist.readBytes((char*)(&len), sizeof(size_t));
//    for (size_t i = 0; i < len; i++)
//    {
//        tmp = name[i];
//        ist.readBytes((char*)(&tmp), sizeof(QChar));
//    }
//}

void userinfo::load_bin(QDataStream& ist)
{
    ist >> surname;
    ist >> login;
    ist >> password;
    ist >> access;
}

void userinfo::print_table_row(QTextStream& ost) const // R переделать ширину поля
{
    ost << surname;
    ost << login;
    ost << password;
    if (access)
        ost << "Доступ есть\n";
    else
        ost << "Доступа нет\n";
}

QString userinfo::getSurname()
{
    return surname;
}

bool userinfo::getAccess() const
{
    return access;
}
