// Вариант 3, задание на 100%

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::ios;
using std::setw;

class User
{
private:
    string surname;
    string login;
    string password;
    bool access;
public:
    void access_read(std::istream& ist, char* name);
    void load_txt(std::istream& ist);
    void save_bin_string(const std::string& name, std::ostream& ost) const;
    void save_bin(std::ostream& ost) const;
    void load_bin_string(std::string& name, std::istream& ist);
    void load_bin(std::istream& ist);
    static void print_table_head(std::ostream& ost);
    void print_table_row(std::ostream& ost) const;
    bool GetAccess() const;
    string GetSurname() const;
};

void User::access_read(std::istream& ist, char* name)
{
    char tmp;
    ist >> tmp;
    for (size_t j = 0; j < 12; j++)
    {
        ist >> name[j];
        if (name[j] == '\"')
        {
            name[j] = '\0';
            break;
        }
        else if (ist.peek() == ' ')
        {
            name[j + 1] = ' ';
            j++;
        }
    }
}

void User::load_txt(std::istream& ist)
{
    ist >> surname;
    ist >> login;
    ist >> password;
    char buf[12];
    access_read(ist, buf);
    if ((strcmp(buf, "Доступ есть")) == 0)
        access = true;
    else
        access = false;
}

void User::save_bin_string(const std::string& name, std::ostream& ost) const
{
    size_t len = name.size();
    ost.write((char*)(&len), sizeof(size_t));
    for (size_t i = 0; i < len; i++)
        ost.write((char*)(&name[i]), sizeof(char));
}

void User::save_bin(std::ostream& ost) const
{
    save_bin_string(surname, ost);
    save_bin_string(login, ost);
    save_bin_string(password, ost);
    ost.write((char*)(&access), sizeof(bool));
}

void User::load_bin_string(std::string& name, std::istream& ist)
{
    size_t len; char tmp;
    ist.read((char*)(&len), sizeof(size_t));
    for (size_t i = 0; i < len; i++)
    {
        ist.read((char*)(&tmp), sizeof(char));
        name += tmp;
    }
}

void User::load_bin(std::istream& ist)
{
    load_bin_string(surname, ist);
    load_bin_string(login, ist);
    load_bin_string(password, ist);
    ist.read((char*)(&access), sizeof(bool));
}

void User::print_table_head(std::ostream& ost)
{
    ost << setw(16) << "Фамилия" << setw(16) << "Логин" <<
        setw(16) << "Пароль" << setw(16) << "Доступ\n";
}

void User::print_table_row(std::ostream& ost) const
{
    ost << setw(16) << surname;
    ost << setw(16) << login;
    ost << setw(16) << password;
    if (access)
        ost << setw(16) << "Доступ есть\n";
    else
        ost << setw(16) << "Доступа нет\n";
}

bool User::GetAccess() const
{
    return access;
}

string User::GetSurname() const
{
    return surname;
}

size_t menu(std::ostream& ost)
{
    size_t choice;
    ost << "Добро пожаловать в лабораторную работу №20!\n";
    ost << "1. Открыть in.txt, вывести на консоль и сохранить bin файл out.dat.'\n";
    ost << "2. Открыть out.dat и вывести на консоль\n";
    do
    {
        ost << "Выберите режим (1/2): ";
        std::cin >> choice;
        if (choice >= 1 && choice <= 2)
            return choice;
        else
            ost << "Неверно указан номер.\n";
    } while (true);
}

std::vector<User> sort(std::vector<User>& data)
{
    size_t len = data.size();
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = i + 1; j < len; j++)
            if (data[i].GetSurname() > data[j].GetSurname())
                std::swap(data[i], data[j]);
    return data;
}

std::size_t save_bin(const std::vector<User>& data, std::ostream& ost)
{
    size_t len = data.size();
    size_t len_tmp = len;
    for (size_t i = 0; i < len; i++)
        if (data[i].GetAccess()) len_tmp--;
    ost.write((char*)(&len_tmp), sizeof(size_t));
    len = 0;
    for (size_t i = 0; i < data.size(); i++)
        if (!data[i].GetAccess())
        {
            data[i].save_bin(ost);
            len++;
        }
    return len;
}

std::size_t load_bin(std::vector<User>& data, std::istream& ist)
{
    size_t len = 0, count = 0;
    ist.read((char*)(&len), sizeof(size_t));
    for (size_t i = 0; i < len; i++, count++)
    {
        User newClass;
        newClass.load_bin(ist);
        data.push_back(newClass);
    }
    return count;
}

std::size_t load_txt(std::vector<User>& data, std::istream& ist)
{
    string n;
    size_t len = 0;
    while (getline(ist, n)) len++; // количество строк
    ist.clear();
    ist.seekg(0); // возращение указателя в исходное место
    if (len < 0) return 0;
    for (size_t i = 0; i < len; i++)
    {
        User newClass;
        newClass.load_txt(ist);
        data.push_back(newClass);
    }
    return len;
}

std::size_t print_table(const std::vector<User>& data, std::ostream& ost)
{
    data.begin()->print_table_head(ost);
    size_t len = 0;
    for (size_t i = 0; i < data.size(); i++, len++) data[i].print_table_row(ost);
    return len;
}

int main()
{
    setlocale(LC_ALL, "");
    size_t choise = menu(cout);
    vector<User> Database;
    size_t len = 0;
    if (choise == 1)
    {
        ifstream ist("in.txt");
        if (!ist.is_open())
        {
            cout << "Программа завершилась с ошибками.\nНевозможно открыть файл.";
            return 0;
        }
        len = load_txt(Database, ist);
        ist.close();
        if (len < 0)
        {
            cout << "Пустой файл.";
            return 0;
        }
        len = print_table(Database, cout);
        cout << "Количество выведенных пользователей: " << len;
        Database = sort(Database);
        ofstream ost_bin("out.dat", ios::binary);
        len = save_bin(Database, ost_bin);
        ost_bin.close();
        cout << "\nКоличество записанных пользователей, "
            << "которые не имеют доступ: " << len;
    }
    else
    {
        ifstream ist("out.dat", ios::binary);
        if (!ist.is_open())
        {
            cout << "Программа завершилась с ошибками.\nНевозможно открыть файл.";
            return 0;
        }
        len = load_bin(Database, ist);
        cout << "Количество загруженных пользователей: " << len << '\n';
        ist.close();
        if (len < 0)
        {
            cout << "Пустой файл.";
            return 0;
        }
        len = print_table(Database, cout);
        cout << "Количество выведенных пользователей: " << len;
    }
    return 0;
}