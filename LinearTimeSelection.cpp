/******************************************************
ʵ��һ���ݹ�����β���1.�ݹ�2.����3.�ϲ�
�������С��ģ���⣨��ͬ�����⣩�Ľ�ϲ�Ϊ
һ����������Ľ⣬�����������������������Ľ�
��������ʱ��ѡ��LinearTimeSelection
Q:������������n��Ԫ�غ�����k���ҳ�n��Ԫ���е�kСԪ��
INPUT����������Ԫ�ظ���n����k��Ԫ��λ��k
OUTPUT:�������еĵ�k��Ԫ��
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
void SelectSort(int*array, int p, int r)                   //ѡ������
{
    for (int i = p; i < r; i++)                            //�����鰴��С����˳������
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
int Partition1(int* array, int p, int r)                 //��x��Ϊ��׼��������ָ����x��λ��
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
        middle = Partition1(array, p, r);                // ���ػ�׼Ԫ��λ��
        Quicksort(array, p, middle - 1);                 // ������ݹ��������
        Quicksort(array, middle + 1, r);                 // ������ݹ��������
    }
}

int SearchMiddle(int* array, int p, int r)         //��ÿ�����λ��,������λ����λ��i
{
    int* b = new int[r - p + 1];                   //����������aͬ�ȴ�С������b
    for (int i = p; i <= r; ++i)                   //������b�������a��ע���ʱb���׵�ַΪ0����a���׵�ַΪp��
    {
        b[i - p] = array[i];
    }
    SelectSort(b, 0, r - p);                      //������b����b[(r-p+1)/2]Ϊ��λ��
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
int Partition2(int* array, int p, int r,int x)   //��x��Ϊ��׼��������ָ����x��λ��
{
    int i = p, j = r + 1;                       //iָ����Ԫ�ص�ǰһ��λ�ã�jָ��βԪ�صĺ�һ��λ��
    while (true)
    {

        while (array[++i] < x && i < r);        //i�ӻ�׼���ұߵ�Ԫ�ؿ�ʼ�ң�ֱ���ҵ���һ�����ڵ��ڻ�׼����Ԫ��
        while (array[--j] > x);                 //j��βԪ�ؿ�ʼ�ң�ֱ���ҵ���һ��С�ڵ��ڻ�׼����Ԫ��
        if (i >= j)                            //��i>=j��˵����׼����λ�����ҵ���Ϊj
        {
            break;
        }
        swap(array[i], array[j]);              //��������Ԫ�أ�ʹ�û�׼����ߵ����������������ұߵ�������С����
    }
    array[p] = array[j];
    array[j] = x;
    return j;                                  //���ػ�׼����λ��
}
int Select(int*array, int p, int r, int k)    //���Ի���
{
    if (r - p < 75)
    {
        SelectSort(array, p, r);
        return array[p + k - 1];
    }
    for (int i = 0; i <= (r - p - 4) / 5; i++)    //�ֳ�n/5�飬ÿ��5�����ҵ�ÿ�����λ���������ŵ�������Ԫ�ص�λ��
    {
        int mid = SearchMiddle(array, p + 5 * i, p + 5 * i + 4);
        swap (array[mid], array[p + i]);
    }
    int m = Select(array, p, p + (r - p - 4) / 5, (r - p - 4) / 10 );    //�ҵ�������λ������λ��
    int i = Partition2(array, p, r, m);                                   //������λ������
    int j = i - p + 1;                                              //���С������ĳ���
    if (k <= j )                         //����С������ĳ���С�ڵ���k��˵����kС��Ԫ������������ڣ�����ݹ�
    {
        return Select(array, p, i, k);
    }
    else                                 //����˵����kС��Ԫ���ڽϴ������飬����ݹ�
    {
        return Select(array, i + 1, r, k - j);
    }
}
int main()
{
    int num;
    printf("������Ԫ�ظ���\n");
    scanf_s("%d", &num);
    while
        (num <= 0)
    {
        printf("����ȷ����Ԫ�ظ���\n");
        scanf_s("%d", &num);
    }

    srand(unsigned(time(0)));                                   //�������������
    int* array = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
    {
        array[i] = rand();
    }

    FILE* fp = fopen("primary data3.txt", "w");                 //���ڡ�primary data3.txt���в鿴����
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
    fp = fopen("processed data3.txt", "w");                    //���ڡ�processed data3.txt���в鿴����
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    printf("�����������Ѵ���processed data3.txt\n ");
    printf("����ʱ��: %lf\n", double(end1 - start1) / CLOCKS_PER_SEC);
    printf("������Ҫ���ҵ�kСԪ����k������\n");
    int k;
    scanf_s("%d", &k);
    clock_t start2 = clock();                                      //����clock(�������������ʱ��
    int result = Select(array, 0, n - 1, k);
    clock_t end2 = clock();
    printf("��k��Ԫ��Ϊ:%d\n",result);
    printf("����ʱ��: %lf\n", double(end2 - start2) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}
