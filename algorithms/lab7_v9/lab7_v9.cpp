#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct object
{
    size_t value;
    size_t capacity;
    float value_per_capacity;
};

bool sort_type_vpc(object a, object b)
{
    return a.value_per_capacity > b.value_per_capacity;
}

float rude_method(vector<object>& objects, size_t max_capacity)
{
    float res_value = 0, res_capacity = max_capacity;
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (res_capacity - objects[i].capacity >= 0)
        {
            res_value += objects[i].value;
            res_capacity -= objects[i].capacity;
        }
        else
        {
            float ratio = (res_capacity * 1.0) / (objects[i].capacity);
            res_value += objects[i].value * ratio;
            res_capacity -= objects[i].capacity * ratio;
            break;
        }
    }
    return res_value;
}

int main()
{
    setlocale(LC_ALL, "");
    int len; size_t max_capacity; vector<object> objects;
    //ifstream ist("in.txt");
    cout << "Введите максимальный размер заполняемой емкости: ";
    cin >> max_capacity;
    cout << "Введите количество предметов: ";
    cin >> len;
    for (size_t i = 1; i <= len; i++)
    {
        object newObject;
        cout << '[' << i << "] ценность: ";
        cin >> newObject.value;
        cout << ", объем: ";
        cin >> newObject.capacity;
        newObject.value_per_capacity = newObject.value / (newObject.capacity * 1.0);
        objects.push_back(newObject);
        cout << endl;
    }
    sort(objects.begin(), objects.end(), sort_type_vpc);
    float res = rude_method(objects, max_capacity);
    cout << "Грубый метод: " << res;
}