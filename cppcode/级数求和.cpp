#include <iostream>
using namespace std;
int main()
{
    int k, n = 0;
    double sum = 0; // 浮点数运算,不能用整数运算
    cin >> k;
    for (int i = 1; i <= 10e7; i++) // for循环会自动将浮点数转换为整数
    {
        sum += 1.0 / i; // 同上
        if (sum > k)    // 此时满足最小的n
        {
            n = i;
            break;
        }
    }
    cout << n << endl;
    return 0;
}