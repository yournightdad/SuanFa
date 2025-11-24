#include <iostream>
using namespace std;
void InsertSort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int end = i;            // 记录有序序列最后一个下标
        int tem = arr[end + 1]; // 记录无序序列的第一个元素
        // 单趟排,递增序列
        while (end >= 0 && tem < arr[end]) // 若有序序列的元素大于无序序列的元素,
        {
            arr[end + 1] = arr[end]; // 后移一位
            end--;                   // 有序序列最后一个下标前移
        }
        arr[end + 1] = tem; // 把tem放到比插入的元素小的位置
    }
    return;
}
// 插入排序
// 1.从第一个元素开始,默认有序序列
// 2.从第二个元素开始,依次插入到前面的有序序列中
// 3.依次类推
// 4.时间复杂度O(n^2),空间复杂度O(1)
// 5.稳定排序
// 6.原地排序
// 7.最坏情况,数组本来就是有序的,每次插入的元素都比有序序列的元素大,需要移动n-1次
// 8.最好情况,数组本来就是有序的,每次插入的元素都比有序序列的元素小,需要移动0次
// 9.原地排序,空间复杂度O(1)
int main()
{
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    InsertSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}