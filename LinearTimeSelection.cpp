/******************************************************
实验一：递归与分治策略1.递归2.调用3.合并
将求出的小规模问题（相同子问题）的解合并为
一个更大问题的解，由下向上依次求出最终问题的解
三、线性时间选择LinearTimeSelection
Q:给定线性序集中n个元素和整数k，找出n个元素中第k小元素
INPUT：线性序集中元素个数n，第k个元素位置k
OUTPUT:线性序集中的第k个元素
LI YANG 2021065408
2023.10.12
******************************************************/

#include <cstdio>
#include <cstdlib>
#include<iostream>
#include<random>
#include <algorithm>
using namespace std;

int n, k; 
void SelectSort(int*array, int p, int r)                   //选择排序
{
    for (int i = p; i < r; i++)                            //将数组按从小到大顺序排列
    {
        int x = i;
        for (int j = i + 1; j <= r; j++)
        {
            if (array[j] < array[x])
            {
                x = j;
            }
        }
        swap(array[i], array[x]);           
    }
}
int Partition1(int* array, int p, int r)                 //将x作为基准数将数组分割，返回x的位置
{
    int i = p, j = r + 1, x = array[p];                  //i指向首元素的前一个位置，j指向尾元素的后一个位置
    while (true)
    {
        while (array[++i] < x && i < r);                 //i从基准数右边的元素开始找，直到找到第一个大于等于基准数的元素
        while (array[--j] > x);                          //j从尾元素开始找，直到找到第一个小于等于基准数的元素
        if (i >= j)                                      //若i>=j，说明基准数的位置已找到，为j
            break;
        swap(array[i], array[j]);                        //交换两个元素，使得基准数左边的数均不大于它，右边的数均不小于它
    }
    array[p] = array[j];
    array[j] = x;
    return j;                                            //返回基准数的位置
}
void Quicksort(int* array, int p, int r)                 //快速排序
{
    int middle;
    if (p < r)
    {
        middle = Partition1(array, p, r);                // 返回基准元素位置
        Quicksort(array, p, middle - 1);                 // 左区间递归快速排序
        Quicksort(array, middle + 1, r);                 // 右区间递归快速排序
    }
}

int SearchMiddle(int* array, int p, int r)         //找每组的中位数,返回中位数的位置i
{
    int* b = new int[r - p + 1];                   //建立与数组a同等大小的数组b
    for (int i = p; i <= r; ++i)                   //用数组b存放数组a（注意此时b的首地址为0，而a的首地址为p）
    {
        b[i - p] = array[i];
    }
    SelectSort(b, 0, r - p);                      //将数组b排序，b[(r-p+1)/2]为中位数
    for (int i = p; i <= r; ++i)
    {
        if (array[i] == b[(r - p + 1) / 2])
        {
            return i;
        }
    }
    delete[]b;
    return 0;
}
int Partition2(int* array, int p, int r,int x)   //将x作为基准数将数组分割，返回x的位置
{
    int i = p, j = r + 1;                       //i指向首元素的前一个位置，j指向尾元素的后一个位置
    while (true)
    {

        while (array[++i] < x && i < r);        //i从基准数右边的元素开始找，直到找到第一个大于等于基准数的元素
        while (array[--j] > x);                 //j从尾元素开始找，直到找到第一个小于等于基准数的元素
        if (i >= j)                            //若i>=j，说明基准数的位置已找到，为j
        {
            break;
        }
        swap(array[i], array[j]);              //交换两个元素，使得基准数左边的数均不大于它，右边的数均不小于它
    }
    array[p] = array[j];
    array[j] = x;
    return j;                                  //返回基准数的位置
}
int Select(int*array, int p, int r, int k)    //线性划分
{
    if (r - p < 75)
    {
        SelectSort(array, p, r);
        return array[p + k - 1];
    }
    for (int i = 0; i <= (r - p - 4) / 5; i++)    //分成n/5组，每组5个，找到每组的中位数并将它放到数组首元素的位置
    {
        int mid = SearchMiddle(array, p + 5 * i, p + 5 * i + 4);
        swap (array[mid], array[p + i]);
    }
    int m = Select(array, p, p + (r - p - 4) / 5, (r - p - 4) / 10 );    //找到各组中位数的中位数
    int i = Partition2(array, p, r, m);                                   //按照中位数划分
    int j = i - p + 1;                                              //求较小数数组的长度
    if (k <= j )                         //若较小数数组的长度小于等于k，说明第k小的元素在这个数组内，将其递归
    {
        return Select(array, p, i, k);
    }
    else                                 //否则，说明第k小的元素在较大数数组，将其递归
    {
        return Select(array, i + 1, r, k - j);
    }
}
int main()
{
    int num;
    printf("请输入元素个数\n");
    scanf_s("%d", &num);
    while
        (num <= 0)
    {
        printf("请正确输入元素个数\n");
        scanf_s("%d", &num);
    }

    srand(unsigned(time(0)));                                   //随机生成数程序
    int* array = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
    {
        array[i] = rand();
    }

    FILE* fp = fopen("primary data3.txt", "w");                 //可在‘primary data3.txt’中查看数据
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    fclose(fp);
    clock_t start1 = clock();                                  
    Quicksort(array, 0, num - 1);
    clock_t end1 = clock();
    fp = fopen("processed data3.txt", "w");                    //可在‘processed data3.txt’中查看数据
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    printf("排序后的序列已存入processed data3.txt\n ");
    printf("排序时间: %lf\n", double(end1 - start1) / CLOCKS_PER_SEC);
    printf("请输入要查找第k小元素中k的数据\n");
    int k;
    scanf_s("%d", &k);
    clock_t start2 = clock();                                      //利用clock(）函数计算查找时间
    int result = Select(array, 0, n - 1, k);
    clock_t end2 = clock();
    printf("第k个元素为:%d\n",result);
    printf("查找时间: %lf\n", double(end2 - start2) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}
