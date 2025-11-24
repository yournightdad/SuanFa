#include <bits/stdc++.h>
using namespace std;

void num(string s, int *mid)
{
    for (int i; i < s.size(); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (s[i] == 'a' + j)
            {
                mid[j]++;
            }
        }
    }
}
int main()
{
    return 0;
}