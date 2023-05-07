#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
    int info;
    Node* next;
};

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

Node* insert_node(Node* head, Node* prev, Node* n)
{
    if (prev == 0)
    {
        n->next = head;
        head = n;
    }
    else
    {
        n->next = prev->next;
        prev->next = n;
        prev = n;
    }
    return head;
}

Node* load_txt(Node* head, istream& ist)
{
    int len;
    ist >> len;
    Node* tail = NULL;
    Node* newNode = 0;
    for (int i = 0; i < len; i++)
    {
        newNode = new Node;
        ist >> newNode->info;
        newNode->next = 0;
        if (tail == 0)
        {
            head = newNode;
        }
        else
        {
            tail->next = newNode;
        }
        tail = newNode;
    }
    return head;
}

void print_list(Node* head, std::ostream& ost)
{
    ost << '\n';
    for (Node* cur = head; cur != NULL; cur = cur->next)
    {
        ost << cur->info << ' ';
    }
}

bool check_number(int number)
{
    size_t c = 0;
    for (int i = 1; i <= number; i++) if ( (number % i) == 0) c++;
    if (c == 2) return true;
    else return false;
}

Node* My_task(Node* head, Node* prev, Node* n)
{
    for (size_t i = 0; i < 5; i++)
    {
        Node* newNode = new Node;
        newNode->info = stoi(generation_number());
        head = insert_node(head, prev, newNode);
    }
    return head;
}

Node* find_number(Node* head)
{
    Node* cur_prev = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next)
    {
        if (check_number(cur->info))
        {
            head = My_task(head, cur_prev, cur);
            return head;
        }
        cur_prev = cur;
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    Node* head = NULL;
    ifstream ist("in.txt");
    head = load_txt(head, ist);
    print_list(head, std::cout);
    head = find_number(head);
    if (head == 0)
    {
        cout << "В узле нет чисел с чётной суммой цифр.";
        return 0;
    }
    print_list(head, std::cout);
    return 0;
}
