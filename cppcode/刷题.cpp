#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n), y(n);

    // 输入坐标数据
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i] >> y[i];
    }

    /****************** y方向处理 ******************/
    // 使用nth_element优化中位数查找（O(n)复杂度）
    nth_element(y.begin(), y.begin() + n / 2, y.end());
    int median_y = y[n / 2];

    // 计算y方向总步数
    int total_steps = 0;
    for (int y_i : y)
    {
        total_steps += abs(y_i - median_y);
    }

    /****************** x方向处理 ******************/
    // 先对x坐标排序（O(nlogn)）
    sort(x.begin(), x.end());

    // 调整x坐标：x[i] = original_x[i] - i
    // 这样调整后，连续队列的要求转化为所有x[i]相同
    for (int i = 0; i < n; ++i)
    {
        x[i] -= i;
    }

    // 再次使用nth_element找中位数
    nth_element(x.begin(), x.begin() + n / 2, x.end());
    int median_x = x[n / 2];

    // 计算x方向总步数
    for (int x_i : x)
    {
        total_steps += abs(x_i - median_x);
    }

    cout << total_steps << endl;
    return 0;
}