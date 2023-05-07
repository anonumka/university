#include "userdata.hpp"
#include <QFile>

std::vector<userinfo> userdata::sort(std::vector<userinfo>& data)
{
    size_t len = data.size();
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = i + 1; j < len; j++)
            if (data[i].userinfo::getSurname() > data[j].userinfo::getSurname())
                std::swap(data[i], data[j]);
    return data;
}

std::size_t userdata::load_txt(std::vector<userinfo>& data, QTextStream& ist)
{
    QString n;
    size_t len = 0;
    while (!ist.atEnd())
    {
        n = ist.readLine();
        len++;
    }
    ist.seek(0);
    if (len == 0) return 0;
    for (size_t i = 0; i < len; i++)
    {
        userinfo newClass;
        newClass.load_txt(ist);
        data.push_back(newClass);
    }
    return len;
}

size_t userdata::save_bin(const std::vector<userinfo>& data, QDataStream& ost)
{
    size_t len = data.size();
    size_t len_tmp = len;
    for (size_t i = 0; i < len; i++)
        if (data[i].userinfo::getAccess()) len_tmp--;
    ost << len_tmp;
    len = 0;
    for (size_t i = 0; i < data.size(); i++)
        if (!data[i].userinfo::getAccess())
        {
            data[i].save_bin(ost);
            len++;
        }
    return len;
}

size_t userdata::load_bin(std::vector<userinfo>& data, QDataStream& ist)
{
    size_t len = 0, count = 0;
    ist >> len;
    for (size_t i = 0; i < len; i++, count++)
    {
        userinfo newClass;
        newClass.load_bin(ist);
        data.push_back(newClass);
    }
    return count;
}

void userdata::print_table_head(QTextStream& ost)
{
    ost.setFieldWidth(13);
    ost.setFieldAlignment(QTextStream::AlignRight);
    ost.setPadChar(' ');
    ost <<"Фамилия" << "Логин"
        << "Пароль" << "Доступ\n";
}

std::size_t userdata::print_table(const std::vector<userinfo>& data, QTextStream& ost)
{
    size_t len = 0;
    print_table_head(ost);
    for (size_t i = 0; i < data.size(); i++, len++)
            data[i].print_table_row(ost);
    ost.setFieldWidth(0);
    return len;
}

userdata::userdata(int choice, QString path_txt, QString path_bin, QTextStream& ost)
{
    std::vector<userinfo> Database;
    size_t len;
    if (choice == 1)
    {
        QFile file_txt(path_txt);
        file_txt.open(QFile::ReadOnly);
        QTextStream ist_txt(&file_txt);
        len = userdata::load_txt(Database, ist_txt);
        if (len == 0)
            ost << "Пустой файл.";
        len = print_table(Database, ost);
        ost << "Выведено: " << len << " пользователей.\n";
        Database = sort(Database);
        QFile file_bin(path_bin);
        file_bin.open(QFile::WriteOnly);
        QDataStream ost_bin(&file_bin);
        len = userdata::save_bin(Database, ost_bin);
        file_bin.close();
        ost << "Пользователи, которые не имеют доступ: " << len << '\n';
        //out_text = QString("%1").arg(len);
    }
    else
    {
        QFile file_bin(path_bin);
        file_bin.open(QFile::ReadOnly);
        QDataStream ist(&file_bin);
        len = load_bin(Database, ist);
        file_bin.close();
        if (len == 0)
            ost << "Пустой файл.";
        len = print_table(Database, ost);
        ost << "Количество выведенных пользователей: " << len << '\n';
    }
}
