#include <iostream>
#include "windows.h"
using namespace std;
#define old 21
#define hight 180.5
#define height 56
int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为utf-8
    cout << "我是周杰伦，今年" << old << "岁。" << endl;
    cout << "身高是" << hight << "cm," << "体重是" << height << "kg。" << endl;
    return 0;
}
// 解决中文乱码问题
// 方法1：引入windows.h头文件，
//       在代码开头加上SetConsoleOutputCP(CP_UTF8);
// 方法2：在main函数内部编写：system("chcp 65001");
