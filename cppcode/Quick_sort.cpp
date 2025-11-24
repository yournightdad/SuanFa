#include <iostream>
using namespace std;
int partSort(int *a, int left, int right) // 挖坑单趟排序
{
    if (left >= right)
    {
        return left; // 当left>=right时，该数组只有一个元素，返回key下标
    }
    int key = a[left]; // 挖坑
    while (left < right)
    {
        while (right > left && a[right] >= key) // 右边大于key，右指针左移,保证右指针仍然大于左指针，防止数组越界
        {
            right--; // 右边大于key，右指针左移
        }
        a[left] = a[right];                    // 右边小于key，将右边元素放到左边，右边形成新的坑                                // 左指针右移
        while (left < right && a[left] <= key) // 同上
        {
            left++; // 左边小于key，左指针右移
        }
        a[right] = a[left]; // 左边大于key，将左边元素放到右边，右边形成新的坑
    }
    int end = right; // 当left=right时，最后的坑位下标就是end
    a[end] = key;    // 将key放到end位置
    return end;      // 返回挖好坑的key下标
}
void quickSort(int *a, int left, int right)
{
    if (left >= right)
    {
        return; // 当left>=right时，该数组只有一个元素，无需排序
    }
    int key = partSort(a, left, right); // 挖坑单趟排序
    quickSort(a, left, key - 1);        // 递归左半部分
    quickSort(a, key + 1, right);       // 递归右半部分
}
int main()
{
    int n = 0;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    quickSort(a, 0, n - 1); // 快速排序
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " "; // 输出排序后的数组
    }
    cout << endl;
    delete[] a;
    return 0;
}