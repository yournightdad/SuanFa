// P1601 A+B Problem（高精）（参考题解写的，非原创）
#include <bits/stdc++.h>
using namespace std;
int main()
{
    const int num = 1000;
    string s1;
    string s2;
    int l1, l2, lsum;
    int a[num], b[num], sum[num];
    memset(a, 0, sizeof(a)); // 数组初始化为某一固定值，初始化0也可以直接a[num]={};
    memset(b, 0, sizeof(b));
    memset(sum, 0, sizeof(sum));
    cin >> s1 >> s2;
    l1 = s1.length();
    l2 = s2.length();
    for (int i = 0; i < l1; i++)
    {
        a[l1 - i - 1] = s1[i] - '0'; // char转化成int,把大数从个位开始一位一位存放在数组a中，方便后续计算
    }
    for (int i = 0; i < l2; i++)
    {
        b[l2 - i - 1] = s2[i] - '0'; // 同上
    }
    l1 > l2 ? lsum = l1 : lsum = l2; // 对于条件表达式b ? x : y，先计算条件b，然后进行判断。如果b的值为true，计算x的值，运算结果为x的值;否则，计算y的值，运算结果为y的值。一个条件表达式绝不会既计算x，又计算y。条件运算符是右结合的，也就是说，从右向左分组计算。例如，a ? b : c ? d : e将按a ? b : (c ? d : e)执行。
    int flag = 0;
    for (int i = 0; i < lsum; i++)
    {
        sum[i] = a[i] + b[i] + flag;
        flag = sum[i] / 10;   // 判断是否有进位
        sum[i] = sum[i] % 10; // 保持数组中每项数字都是个位
    }
    if (flag == 1)
    { // 判断最高位是否进位
        lsum++;
        sum[lsum - 1] += flag;
    }
    for (int i = lsum - 1; i >= 0; i--) // 反向读一遍所有字符,因为前面都是从个位开始存放数字
    {
        cout << sum[i];
    }
    cout << endl;
    return 0;
}
