#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using std::cin;
using std::cout;
using std::ios;
using std::ios_base;
using std::ifstream;
using std::swap;
using std::setw;
using std::ofstream;

const int size_surname = 16;
const int size_login = 16;
const int size_password = 16;
const int size_access = 17;

struct UserAccess
{
    char surname[size_surname];
    char login[size_login];
    char password[size_password];
    bool access;
};

int menu()
{
    size_t choice;
    cout << "Добро пожаловать в лабораторную работу N 16!\n";
    cout << "1. Открыть in.txt, вывести на консоль и сохранить bin файл out.dat.'\n";
    cout << "2. Открыть out.dat и вывести на консоль\n";
    do
    {
        cout << "Выберите режим (1/2): ";
        cin >> choice;
        if (choice >= 1 && choice <= 2)
            return choice;
        else
            cout << "Неверно указан номер.\n";
    } while (true);
}

UserAccess* sort(UserAccess* data, std::size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = i + 1; j < len; j++)
            if ((strcmp(data[i].surname, data[j].surname)) > 0)
                swap(data[i], data[j]);
    return data;
}

void print_data(const UserAccess* data, std::size_t& len, std::ostream& ost)
{
    ost << setw(size_surname) << "Фамилия" << setw(size_login) << "Логин" <<
        setw(size_password) << "Пароль" << setw(size_access) << "Доступ\n";
    for (size_t i = 0; i < len; i++)
    {
        ost << setw(size_surname) << data[i].surname;
        ost << setw(size_login) << data[i].login;
        ost << setw(size_password) << data[i].password;
        if (data[i].access)
            ost << setw(size_access) << "Доступ есть\n";
        else
            ost << setw(size_access) << "Доступа нет\n";
    }
}

void save_bin(const UserAccess* data, std::size_t len, std::ostream& ost)
{
    size_t len_tmp = len;
    for (size_t i = 0; i < len; i++)
        if (data[i].access) len_tmp--;
    ost.write((char*)(&len_tmp), sizeof(size_t));
    for (size_t i = 0; i < len; i++)
        if (!data[i].access)
            ost.write((char*)(&data[i]), sizeof(UserAccess));
}

UserAccess* load_bin(std::istream& ist, std::size_t& len)
{
    ist.read((char*)(&len), sizeof(size_t));
    UserAccess* data = new UserAccess[len];
    ist.read((char*)(data), len * sizeof(UserAccess));
    return data;
}

void access_read(std::istream& ist, char* name)
{
    char tmp;
    ist >> tmp;
    for (size_t j = 0; j < size_access; j++)
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

UserAccess* load_txt(std::istream& ist, std::size_t& len)
{
    std::string n;
    len = 0;
    while (getline(ist, n)) len++;
    ist.clear();
    ist.seekg(0);
    if (len < 0)
    {
        cout << "Длина не может быть меньше или равна нулю!";
        len = NULL;
    }
    UserAccess* data = new UserAccess[len];
    char buf[size_access];
    for (size_t i = 0; i < len; i++)
    {
        ist >> data[i].surname;
        ist >> data[i].login;
        ist >> data[i].password;
        access_read(ist, buf);
        if ((strcmp(buf, "Доступ есть")) == 0)
            data[i].access = true;
        else
            data[i].access = false;
    }
    return data;
}

int main()
{
    setlocale(LC_ALL, "");
    int choice = menu();
    UserAccess* data;
    size_t len = 0;
    if (choice == 1)
    {
        ifstream ist("in.txt");
        if (!ist.is_open())
        {
            cout << "Программа завершилась с ошибками.\nНевозможно открыть файл.";
            return 0;
        }
        data = load_txt(ist, len);
        print_data(data, len, std::cout);
        ofstream ost_bin("out.dat", ios::binary);
        data = sort(data, len);
        save_bin(data, len, ost_bin);
        ost_bin.close();
    }
    else
    {
        ifstream ist("out.dat", ios::binary);
        if (!ist.is_open())
        {
            cout << "The program terminated with errors.\nUnable open a file.";
            return 0;
        }
        data = load_bin(ist, len);
        ist.close();
        print_data(data, len, std::cout);
    }
    return 0;
}