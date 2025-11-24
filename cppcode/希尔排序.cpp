#include <iostream>
using namespace std;
void ShellSort(int *arr, int len)
{
    int gap = len;
    while (gap > 1) // 希尔增量序列
    {
        // 每次对gap折半操作
        gap = gap / 2;
        // 对每个分组进行插入排序
        for (int i = 0; i < len - gap; i++)
        {
            int end = i;                       // 记录当前分组有序序列的最后一个下标
            int tem = arr[end + gap];          // 记录当前分组无序序列的第一个元素，即要插入的元素
            while (end >= 0 && tem < arr[end]) // 插入排序
            {
                arr[end + gap] = arr[end]; // 后移
                end = end - gap;           // 有序下标前移
            }
            arr[end + gap] = tem; // 插入
        }
    }
    return;
}
// 希尔排序
//  希尔排序是插入排序的改进版，也称缩小增量排序
//  希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序。
//  希尔排序的增量序列的选择与证明是个数学难题，目前还没有最佳增量序列。
//  希尔排序的代码实现相对简单。
//  希尔排序是不稳定的排序方法。
//  希尔排序的时间复杂度比O(nlog2n)的排序（快速排序，归并排序）要低，为O(n1.3)。

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    ShellSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}