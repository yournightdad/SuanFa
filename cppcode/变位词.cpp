#include <iostream>
#include <string>
using namespace std;
void num(string s, int *f)
{
    for (int j = 0; j < s.size(); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            if (s[j] == 'a' + i)
            {
                f[i]++;
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    string s1, s2;
    for (int i = 0; i < n; i++)
    {
        cin >> s1 >> s2;
        int f1[26] = {0};
        int f2[26] = {0};
        num(s1, f1);
        num(s2, f2);
        for (int j = 0; j < 26; j++)
        {
            if (f1[j] != f2[j])
            {
                cout << "No" << endl;
                break;
            }
            else if (j == 25)
            {
                cout << "Yes" << endl;
            }
        }
    }
    return 0;
}