/******************************************************
ʵ��һ���ݹ�����β���1.�ݹ�2.����3.�ϲ�
�������С��ģ���⣨��ͬ�����⣩�Ľ�ϲ�Ϊ
һ����������Ľ⣬�����������������������Ľ�
������������QuickSort
Q:����n������Ԫ�أ�ͨ���ֽ⡢�ݹ���⡢�ϲ������ų���������
INPUT��Ҫ�����Ԫ�ظ���n
OUTPUT:һ������n��Ԫ�ص���������
LI YANG 2021065408
2023.10.11
******************************************************/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int Partition(int* array, int p, int r)                  //��x��Ϊ��׼��������ָ����x��λ��
{
	int i = p, j = r + 1, x = array[p];                  //iָ����Ԫ�ص�ǰһ��λ�ã�jָ��βԪ�صĺ�һ��λ��
	while (true)
	{
		while (array[++i] < x && i < r);                 //i�ӻ�׼���ұߵ�Ԫ�ؿ�ʼ�ң�ֱ���ҵ���һ�����ڵ��ڻ�׼����Ԫ��
		while (array[--j] > x);                          //j��βԪ�ؿ�ʼ�ң�ֱ���ҵ���һ��С�ڵ��ڻ�׼����Ԫ��
		if (i >= j)                                      //��i>=j��˵����׼����λ�����ҵ���Ϊj
			break; 
		swap(array[i], array[j]);                        //��������Ԫ�أ�ʹ�û�׼����ߵ����������������ұߵ�������С����
	}
	array[p] = array[j];
	array[j] = x;
	return j;                                            //���ػ�׼����λ��
}
void Quicksort(int* array, int p, int r)                 //��������
{
	int middle;
	if (p < r)
	{
		middle = Partition(array, p, r);                 // ���ػ�׼Ԫ��λ��
		Quicksort(array, p, middle - 1);                 // ������ݹ��������
		Quicksort(array, middle + 1, r);                 // ������ݹ��������
	}
}
int main()
{
	int  num;
	printf("������Ҫ��������ݵĸ���:\n");
	scanf_s("%d", &num);
	while
		(num <= 0)
	{
		printf("����ȷ�������ݸ���:\n");
		scanf_s("%d", &num);
	}

	srand(unsigned(time(0)));                             //�������������
	int* array = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++)
	{
		array[i] = rand();


	}
	FILE* fp = fopen("primary data2.txt", "w");           //���ڡ�primary data2.txt���в鿴����
	for (int i = 0; i < num; i++)
	{
		if (i % 20 == 0)
			fprintf(fp, "\n%d", array[i]);
		else
			fprintf(fp, " %d ", array[i]);
	}
	fclose(fp);
	printf("��ʼ���������ɲ�����primary data2.txt \n");
	clock_t start = clock();
	Quicksort(array, 0, num - 1);
	clock_t end = clock();
	fp = fopen("processed data2.txt", "w");                //���ڡ�processed data2.txt���в鿴����
	for (int i = 0; i < num; i++)
	{
		if (i % 20 == 0)
			fprintf(fp, "\n%d", array[i]);
		else
			fprintf(fp, " %d ", array[i]);
	}
	printf("�����������Ѵ���processed data2.txt\n ");
	printf("����ʱ��: %lf\n", double(end - start) / CLOCKS_PER_SEC);
	free(array);
	return 0;
}
