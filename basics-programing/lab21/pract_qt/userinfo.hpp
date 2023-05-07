#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
#include <QTextStream>
#include <QDataStream>

class userinfo
{
    QString surname;
    QString login;
    QString password;
    bool access;
public:
    userinfo();
    bool access_read(QTextStream& ist);
    void load_txt(QTextStream& ist);
    void save_bin_string(const QString& name, QDataStream& ost) const;
    void save_bin(QDataStream& ost) const;
    void load_bin_string(QString& name, QDataStream& ist);
    void load_bin(QDataStream& ist);
    void print_table_row(QTextStream& ost) const;
    QString getSurname();
    bool getAccess() const;
};

#endif // USERINFO_H
