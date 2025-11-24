#include <iostream>
using namespace std;

int main()
{
    long num[100] = {}, flag = 0;
    for (int i = 0; i < 100; i++)
    {
        cin >> num[i];
        if (num[i] == 0)
        {
            flag == i;
        }
    }
    for (int i = flag - 1; i >= 0; i--)
    {
        cout << num[i] << " ";
    }
    return 0;
}