#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

int* delete_substring_arr(int* arr1, int* arr2, int* arr_res, int n, int m)
{
    int k = 0; bool str_deleted = false;
    for (int i = 0; i < n; i++)
    {
        if (arr1[i] == arr2[0])
        {
            int tmp_i = i;
            i++;
            for (int j = 1; j <= m; j++, i++)
            {
                if (j == m)
                {
                    str_deleted = true;
                    i--;
                }
                if (arr1[i] != arr2[j]) break;
            }
            if (!str_deleted)
            {
                i = tmp_i;
                arr_res[k] = arr1[i];
                k++;
            }
        }
        else
        {
            arr_res[k] = arr1[i];
            k++;
        }
    }
    return arr_res;
}

//stack<int> delete_substring_stack(stack<int> stack_s1, stack<int> stack_s2)
//{
//    stack<int> res;
//    int size_s1 = stack_s1.size();
//    int size_s2 = stack_s2.size();
//    bool str_deleted = false;
//    for (int i = 0; i < size_s1; i++)
//    {
//        if (stack_s1.top() == stack_s2.top())
//        {
//            for (int j = 0; j < size_s2; j++, i++)
//            {
//                if (stack_s1.top() != stack_s2.top())
//                {
//                    int i = i + j;
//                }
//            }
//        }
//        else
//        {
//            res.push(stack_s1.top());
//            stack_s1.pop();
//        }
//    }
//    return res;
//}

vector<int> fill_vector(stack<int> stack)
{
    vector<int> res;
    int size_stack = stack.size();
    res.resize(size_stack);
    for (int i = 0; i < size_stack; i++)
    {
        res[i] = stack.top();
        stack.pop();
    }
    return res;
}

stack<int> delete_substring_stack(stack<int> stack_s1, stack<int> stack_s2)
{
    stack<int> res;
    vector<int> s1;
    vector<int> s2;
    s1 = fill_vector(stack_s1);
    s2 = fill_vector(stack_s2);
    bool str_deleted = false;

    for (int i = 0; i < stack_s1.size(); i++)
    {
        if (s1[i] != s2[0])
            res.push(s1[i]);
        else
        {
            int tmp_i = i;
            i++;
            for (int j = 1; j <= s2.size(); j++, i++)
            {
                if (j == s2.size())
                {
                    str_deleted = true;
                    i--;
                    break;
                }
                if (s1[i] != s2[j]) break;
            }
            if (!str_deleted)
            {
                i = tmp_i;
                res.push(s1[i]);
            }
        }
    }


    return res;
}

int* fill_arr(string s, int* arr, int n)
{
    for (int i = 0; i < n; i++) arr[i] = (int)s[i];
    return arr;
}

stack<int> fill_stack(string s, stack<int> stk)
{
    for (int i = 0; i < s.size(); i++)
    {
        stk.push(s[i]);
    }
    return stk;
}

void print_arr(int* arr, int n)
{
    cout << "\nРезультат очереди: ";
    for (int i = 0; i < n; i++) cout << (char)(arr[i]);
}

void print_stack(stack<int> stk)
{
    int n = stk.size();
    cout << "\nРезультат очереди: ";
    for (int i = 0; i < n; i++)
    {
        cout << (char)(stk.top());
        stk.pop();
    }
}

int main()
{
    setlocale(LC_ALL, "");
    string s1, s2;
    cout << "Введите основную строку: ";
    cin >> s1;
    cout << "Введите подстроку, которую нужно удалить: ";
    cin >> s2;
    size_t find = s1.find(s2);
    if (find == string::npos)
    {
        cout << '\'' << s2 << '\'' << " не является подстрокой строки " << '\'' << s1 << '\'';
    }

    size_t size_s1 = s1.size();
    size_t size_s2 = s2.size();
    int* arr_s1 = new int[size_s1];
    int* arr_s2 = new int[size_s2];
    stack<int> stk_s1;
    stack<int> stk_s2;
    stack<int> stk_res;

    arr_s1 = fill_arr(s1, arr_s1, size_s1);
    arr_s2 = fill_arr(s2, arr_s2, size_s2);
    stk_s1 = fill_stack(s1, stk_s1);
    stk_s2 = fill_stack(s2, stk_s2);

    int* arr_res = new int[size_s1 - size_s2];
    arr_res = delete_substring_arr(arr_s1, arr_s2, arr_res, s1.size(), s2.size());
    print_arr(arr_res, size_s1 - size_s2);
    delete[] arr_s1;
    delete[] arr_s2;
    delete[] arr_res;

    stk_res = delete_substring_stack(stk_s1, stk_s2);
    print_stack(stk_res);

    return 0;
}