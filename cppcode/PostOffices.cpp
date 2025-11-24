#include <bits/stdc++.h>
using namespace std;
bool cmp(int a, int b)
{
    return a < b;
}
int main()
{
    int n;
    cin >> n;
    int x[10000], y[10000];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }
    sort(x, x + n, cmp);
    sort(y, y + n, cmp);
    int xmid = x[n / 2], ymid = y[n / 2];
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += abs(x[i] - xmid) + abs(y[i] - ymid);
    }
    cout << sum << endl;
}