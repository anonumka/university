#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    size_t size, sum;
    cout << "Введите сумму: ";
    cin >> sum;
    cout << "Введите количество номиналов: ";
    cin >> size;
    vector<size_t> coins; vector<size_t> count;
    for (size_t i = 1; i <= size; i++)
    {
        int tmp;
        cout << "Введите номинал " << i << " монетки: ";
        cin >> tmp;
        coins.push_back(tmp);
        count.push_back(0);
    }
    sort(coins.begin(), coins.end());

    int coins_amount = 0;
    while (sum > 0)
    {
        for (int i = coins.size() - 1; i >= 0; i--)
            if (sum >= coins[i]) 
            {
                coins_amount += sum / coins[i];
                sum %= coins[i];
            }
    }

    size_t res = 0;
    cout << "\nРезультат: \n" << coins_amount;
    for (size_t i = 0; i < coins.size(); i++)
    {
        cout << "Монета номиналом " << coins[i] << " потребуется " << count[i] << " раз.\n";
        res += count[i];
    }
    cout << "Количество требуемых монет: " << res;
    cout << "\nОстаточная сумма: " << sum;
}