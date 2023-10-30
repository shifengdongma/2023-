/******************************************************
实验一：递归与分治策略1.递归2.调用3.合并
将求出的小规模问题（相同子问题）的解合并为
一个更大问题的解，由下向上依次求出最终问题的解
二、快速排序QuickSort
Q:给定n个无序元素，通过分解、递归求解、合并将其排成有序数列
INPUT：要排序的元素个数n
OUTPUT:一个含有n个元素的有序数组
LI YANG 2021065408
2023.10.11
******************************************************/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int Partition(int* array, int p, int r)                  //将x作为基准数将数组分割，返回x的位置
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
		middle = Partition(array, p, r);                 // 返回基准元素位置
		Quicksort(array, p, middle - 1);                 // 左区间递归快速排序
		Quicksort(array, middle + 1, r);                 // 右区间递归快速排序
	}
}
int main()
{
	int  num;
	printf("请输入要排序的数据的个数:\n");
	scanf_s("%d", &num);
	while
		(num <= 0)
	{
		printf("请正确输入数据个数:\n");
		scanf_s("%d", &num);
	}

	srand(unsigned(time(0)));                             //随机生成数程序
	int* array = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++)
	{
		array[i] = rand();


	}
	FILE* fp = fopen("primary data2.txt", "w");           //可在‘primary data2.txt’中查看数据
	for (int i = 0; i < num; i++)
	{
		if (i % 20 == 0)
			fprintf(fp, "\n%d", array[i]);
		else
			fprintf(fp, " %d ", array[i]);
	}
	fclose(fp);
	printf("初始数据已生成并存入primary data2.txt \n");
	clock_t start = clock();
	Quicksort(array, 0, num - 1);
	clock_t end = clock();
	fp = fopen("processed data2.txt", "w");                //可在‘processed data2.txt’中查看数据
	for (int i = 0; i < num; i++)
	{
		if (i % 20 == 0)
			fprintf(fp, "\n%d", array[i]);
		else
			fprintf(fp, " %d ", array[i]);
	}
	printf("排序后的序列已存入processed data2.txt\n ");
	printf("排序时间: %lf\n", double(end - start) / CLOCKS_PER_SEC);
	free(array);
	return 0;
}
