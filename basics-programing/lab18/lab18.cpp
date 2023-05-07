// Вариант - 3, на 100%

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Node
{
    int info;
    Node* next;
    Node* prev;
};
struct List
{
    Node* head;
    Node* tail;
};

int menu()
{
    int choice; int num_element;
    do
    {
        cout << "\nDo you want to delete element of list?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << "Choice mode: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nChoice number of element: ";
            cin >> num_element;
            if (num_element > 0) return num_element;
            else
            {
                cout << "\nNumber should be '>' 0";
                break;
            }
        case 2:
            cout << "\nFinish programm...";
            return -1;
        default:
            cout << "\nIncorrect enter number.";
            break;
        }
    } while (true);
}

void remove_node(List& list, Node* n)
{
    if (n->prev == nullptr)
    {
        n = n->next;
        n->prev = nullptr;
        list.head = n;
    }
    else if (n->next == nullptr)
    {
        n = n->prev;
        n->next = nullptr;
        list.tail = n;
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
}

void delete_node(List& list)
{
    Node* delete_element = list.head;
    int index;
    cout << "Введите номер узла: ";
    cin >> index;
    if (index < 1)
    {
        cout << "Введите номер узла повторно: ";
        return;
    }
    for (int i = 0; i < index - 1; i++)
    {
        if (delete_element->next == 0)
        {
            cout << "Введите номер узла повторно: ";
            return;
        }
        delete_element = delete_element->next;
    }
    remove_node(list, delete_element);
}

void insert_node(List& list, Node* next, Node* n)
{
    if ((list.head == 0) && (list.tail == 0))
    {
        list.head = list.tail = n;
        Node* cur = list.head;
        cur->next = n;
        n->prev = cur;
        cur = n;
        n->next = 0;
        list.head->prev = 0;
    }
    else if (next == 0)
    {
        list.tail->next = n;
        n->prev = list.tail;
        list.tail = n;
        list.tail->next = 0;
    }
    else if (next->prev == 0)
    {
        n->next = next;
        n->prev = next->prev;
        next->prev = n;
        list.head = n;
    }
    else
    {
        n->next = next;
        n->prev = next->prev;
        next->prev = n;
        n->prev->next = n;
    }
}

List& load_txt(Node* head, istream& ist)
{
    Node* prevNode = 0;
    List list;
    list.head = list.tail = 0;
    int tmp;
    while (ist >> tmp)
    {
        Node* newNode = new Node;
        newNode->info = tmp;
        insert_node(list, 0, newNode);
        prevNode = newNode;
    }
    return list;
}

void print_list(List& list, std::ostream& ost)
{
    ost << '\n';
    for (Node* cur = list.head; cur != NULL; cur = cur->next)
    {
        ost << cur->info << ' ';
    }
}
void print_list_rev(List& list, std::ostream& ost)
{
    ost << '\n';
    for (Node* cur = list.tail; cur != NULL; cur = cur->prev)
    {
        ost << cur->info << ' ';
    }
}

string generation_number()
{
    int n = 0, i = 0;
    string res;
    int tmp = 0;
    n = rand() % 256 + 1;
    do
    {
        tmp = n % 2;
        if (tmp)
            res += "1";
        else
            res += "0";
        n /= 2;
    } while (n > 0);
    return res;
}

void My_task(List* list, Node* n)
{
    for (size_t i = 0; i < 5; i++)
    {
        Node* newNode = new Node;
        insert_node(*list, n, newNode);
        newNode->info = stoi(generation_number()); // stoi - convert string to int
        n = newNode;
    }
}

bool check_number(int number)
{
    size_t c = 0;
    for (int i = 1; i <= number; i++)
        if ((number % i) == 0) c++;
    if (c == 2) return true;
    else return false;
}

Node* find_number(List& list)
{
    for (Node* cur = list.head; cur != NULL; cur = cur->next)
    {
        if (check_number(cur->info)) return cur;
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    Node* head = NULL;
    ifstream ist("in.txt");
    List list = load_txt(head, ist);
    print_list(list, std::cout);
    print_list_rev(list, std::cout);
    Node* cur = find_number(list);
    if (cur == 0)
    {
        cout << "\nВ узле нет простых чисел.";
        return 0;
    }
    My_task(&list, cur);
    print_list(list, std::cout);
    print_list_rev(list, std::cout);
    int mode = 0;
    cout << "\nУдалить узел? \n1. Да\n2. Нет" << endl;
    cin >> mode;
    while (mode < 1 || mode > 2)
    {
        cout << "Вы можете выбрать только 1 или 2!\nВведите да или нет повторно: ";
        cin >> mode;
    }
    if (mode == 1)
    {
        delete_node(list);
        print_list(list, std::cout);
        print_list_rev(list, std::cout);

    }
    return 0;
}