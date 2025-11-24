#include <iostream>
using namespace std;
int main()
{
    int l, m;
    int u = 0, v = 0;
    cin >> l >> m;
    int tree[l + 1] = {}; // 初始化，坐标处存在树置为0，被移走置为1
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        for (int j = u; j <= v; j++)
        {
            if (tree[j] == 0)
            { // 判断此处是否有树，有树则移走
                tree[j] = 1;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i <= l; i++)
    {
        if (tree[i] == 0)
        {
            sum++; // 统计树的数量
        }
    }
    cout << sum << endl;
    return 0;
}