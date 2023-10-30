/******************************************************
实验一：递归与分治策略1.递归2.调用3.合并
将求出的小规模问题（相同子问题）的解合并为
一个更大问题的解，由下向上依次求出最终问题的解
一、二分搜索BinarySearch
Q:给定已排好序的n个元素array[0:n-1],在这n个元素中找出一特定元素x
INPUT：数组中元素个数n，特定元素x
OUTPUT：特定元素x在排好序的数组中的位置
LI YANG 2021065408
2023.10.11
******************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int BinarySearch(int* array, int left, int right, int k)      //二分搜索函数
{
    int middle;
    int back = -1;
    while (left <= right)
    {
        middle = (left + right) / 2;                      
        if                                                    //小于基准，在左边数组中
            (array[middle] < k)
            left = middle + 1;
        else if                                               //大于基准，在右边数组中
            (array[middle] > k)
            right = middle - 1;
        else
        {
            back = middle;
            break;
        }

    }
    return back;

}

int main()
{
    int num;
    printf("请输入数组的长度\n");
    scanf("%d", &num);
    while(num <= 0)
    {
        printf("请正确输入数组长度\n");
        scanf("%d", &num);
    }

    srand(unsigned(time(0)));                                   //随机生成数程序
    int* array = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
    {
        array[i] = rand();
    }

    FILE* fp = fopen("primary data1.txt", "w");                  //可在‘primary data1.txt’中查看数据
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    fclose(fp);
    sort(array, array + num);                                   //sort函数将生成的随机数排序
    printf("已按从小到大的顺序排序\n");
    fp = fopen("processed data1.txt", "w");                     //可在‘processed data1.txt’中查看数据
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    fclose(fp);

    printf("\n请输入要查找的元素\n");
    int key;
    scanf("%d", &key);
    clock_t start = clock();
    int location = BinarySearch(array, 0, num - 1, key);        //利用clock（）函数测试函数运行时间
    clock_t end = clock();
    if (location == -1)
        printf("查找失败\n");
    else
        printf("该元素在数组中的位置：%d(从零开始)\n", location);
    printf("查找时间: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}

