#include <iostream>
using namespace std;
void Merge(int *a, int left, int mid, int right) // 合并函数
{
    int *temp = new int[right - left + 1]; // 创建临时数组
    int i = 0, j = left, k = mid + 1;
    while (j <= mid && k <= right)
    {
        if (a[j] <= a[k])
        {
            temp[i++] = a[j++]; // 将较小的元素放入temp数组中
        }
        else
        {
            temp[i++] = a[k++]; // 将较小的元素放入temp数组中
        }
    }
    while (j <= mid)
    {
        temp[i++] = a[j++]; // 将剩余的元素放入temp数组中
    }
    while (k <= right)
    {
        temp[i++] = a[k++]; // 将剩余的元素放入temp数组中
    }
    i = 0; // 将temp数组中的元素复制回原数组a中
    for (int j = left; j <= right; j++)
    {
        a[j] = temp[i++]; // 将temp数组中的元素复制回原数组a中
    }
    delete[] temp; // 释放临时数组
}
void MergeSort(int *a, int left, int right) // 归并排序函数
{
    if (left >= right)
    {
        return; // 只有一个元素，最小有序子序列，直接返回
    }
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);      // 递归调用，将数组a分成左右两部分
    MergeSort(a, mid + 1, right); // 递归调用，将数组a分成左右两部分
    Merge(a, left, mid, right);   // 合并两个有序子序列
}
int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    MergeSort(a, 0, n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        if ((i + 1) % 10 == 0 && i > 0)
        {
            cout << a[i] << endl; // 每输出10个数换行
        }
        else
        {
            cout << a[i] << "  "; // 输出排序后的数组,tmd这里要输出两个空格
        }
    }
    cout << a[n - 1] << endl;
    delete[] a; // 释放数组a的内存
    return 0;
}