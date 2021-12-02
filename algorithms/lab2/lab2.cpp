#include <iostream>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node
{
    int info;
    Node* next;
};

Node* bubbleSortNode(Node* head)
{
    bool sort = true;
    while (sort) 
    {
        sort = false;
        Node* prev = head;
        for (Node* cur = head->next; cur != NULL; cur = cur->next)
        {
            if (prev->info > cur->info)
            {
                swap(prev->info, cur->info);
                sort = true;
            }
            prev = cur;
        }
    }
    return head;
}

queue<int> bubblesortQueue(queue<int> q1)
{
    vector<int> v;
    size_t size = q1.size();
    for (size_t i = 0; i < size; i++)
    {
        v.push_back(q1.front());
        q1.pop();
    }

    bool sort = true;
    while (sort)
    {
        sort = false;
        for (size_t i = 1; i < size; i++)
        {
            if (v[i - 1] > v[i])
            {
                swap(v[i - 1], v[i]);
                sort = true;
            }
        }
    }

    queue<int> q2;
    for (size_t i = 0; i < size; i++) q2.push(v[i]);
    return q2;
}

queue<int> push_pop(queue<int>& q)
{
    int tmp = q.front();
    q.push(tmp);
    q.pop();
    return q;
}

queue<int> bubblesortQueue2(queue<int> &q)
{
    int n = q.size(); bool sort = true;
    int tmp;
    for (int i = 0; i < n; i++)
    {
        int minIndex = -1;
        int minValue = INT_MAX;
        for (int j = 0; j < n - i; j++)
        {
            if (q.front() < minValue)
            {
                minValue = q.front();
                minIndex = j;
            }
            push_pop(q);
        }
        for (int j = 0; j < i + minIndex; j++)
            push_pop(q);

        int minElem = q.front();
        q.pop();
        for (int j = minIndex + 1; j < n; j++)
            push_pop(q);

        q.push(minElem);
    }
    return q;
}

Node* write_node(Node* head, int n, int* arr)
{
    Node* tail = NULL;
    for (int i = 0; i < n; i++)
    {
        Node* newNode = new Node;
        newNode->info = arr[i];
        newNode->next = NULL;
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

queue<int> write_queue(int* arr, int n)
{
    queue<int> q;
    for (size_t i = n; i > 0; i--) q.push(arr[i-1]);
    //size_t i = 0; i < n; i++
    return q;
}

void delete_list(Node* head)
{
    Node* cur = head;
    while (cur->next != nullptr)
    {
        Node* tail = head;
        while (tail->next->next != nullptr) tail = tail->next;
        delete tail->next;
        tail->next = nullptr;
    }
    head = NULL;
}

void print_list(Node* head)
{
    cout << "\n";
    for (Node* cur = head; cur != NULL; cur = cur->next)
        cout << cur->info << ' ';
}

void print_queue(queue<int> q)
{
    size_t size = q.size();
    cout << "\n";
    for (size_t i = 0; i < size; i++)
    {
        cout << q.front() << ' ';
        q.pop();
    }
}

int generate_number()
{
    int n = rand() % 256 + 1;
    return n;
}

int* fill_array(int* arr, int n)
{
    for (int i = 0; i < n; i++) arr[i] = generate_number();
    return arr;
}

int main()
{
    setlocale(LC_ALL, "");
    float res;
    for (size_t n = 1; n <= 100; n*=10)
    {
        int* arr = new int[n];
        arr = fill_array(arr, n);
        cout << "----------------------" << endl;
        cout << "Количество элементов: " << n;

        //Node* head = NULL;
        //head = write_node(head, n, arr);
        //cout << "\nCurrent FIFO: ";
        //print_list(head);

        auto t1 = high_resolution_clock::now();
        //head = bubbleSortNode(head);
        auto t2 = high_resolution_clock::now();
        //res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
        //cout << "\nFIFO заняла " << res << " мс.";

        //cout << "\nSorted FIFO: ";
        //print_list(head);

        //delete_list(head);
        //delete head;

        queue<int> q = write_queue(arr, n);
        cout << "\nCurrent FILO: ";
        print_queue(q);
        t1 = high_resolution_clock::now();
        q = bubblesortQueue2(q);
        t2 = high_resolution_clock::now();
        res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
        cout << "\nSorted FILO: ";
        print_queue(q);
        cout << "\nFILO заняла " << res << " мс." << endl;
        cout << endl;
    }
    return 0;
}