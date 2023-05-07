#ifndef USERDATA_H
#define USERDATA_H
#include "userinfo.hpp"
#include <QString>
#include <QFile>
#include <QDataStream>

using std::string;

class userdata
{
public:
    userdata(int choice, QString path_txt, QString path_bin, QTextStream& ost);
private:
    std::vector<userinfo> sort(std::vector<userinfo>& data);
    std::size_t load_txt(std::vector<userinfo>& data,  QTextStream& ist);
    void print_table_head(QTextStream& ost);
    std::size_t print_table(const std::vector<userinfo>& data, QTextStream& ost);
    size_t save_bin(const std::vector<userinfo>& data, QDataStream& ost);
    size_t load_bin(std::vector<userinfo>& data, QDataStream& ost);
};

#endif // USERDATA_H
