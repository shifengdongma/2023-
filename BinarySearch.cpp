/******************************************************
ʵ��һ���ݹ�����β���1.�ݹ�2.����3.�ϲ�
�������С��ģ���⣨��ͬ�����⣩�Ľ�ϲ�Ϊ
һ����������Ľ⣬�����������������������Ľ�
һ����������BinarySearch
Q:�������ź����n��Ԫ��array[0:n-1],����n��Ԫ�����ҳ�һ�ض�Ԫ��x
INPUT��������Ԫ�ظ���n���ض�Ԫ��x
OUTPUT���ض�Ԫ��x���ź���������е�λ��
LI YANG 2021065408
2023.10.11
******************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int BinarySearch(int* array, int left, int right, int k)      //������������
{
    int middle;
    int back = -1;
    while (left <= right)
    {
        middle = (left + right) / 2;                      
        if                                                    //С�ڻ�׼�������������
            (array[middle] < k)
            left = middle + 1;
        else if                                               //���ڻ�׼�����ұ�������
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
    printf("����������ĳ���\n");
    scanf("%d", &num);
    while(num <= 0)
    {
        printf("����ȷ�������鳤��\n");
        scanf("%d", &num);
    }

    srand(unsigned(time(0)));                                   //�������������
    int* array = (int*)malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
    {
        array[i] = rand();
    }

    FILE* fp = fopen("primary data1.txt", "w");                  //���ڡ�primary data1.txt���в鿴����
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    fclose(fp);
    sort(array, array + num);                                   //sort���������ɵ����������
    printf("�Ѱ���С�����˳������\n");
    fp = fopen("processed data1.txt", "w");                     //���ڡ�processed data1.txt���в鿴����
    for (int i = 0; i < num; i++)
    {
        if (i % 20 == 0)
            fprintf(fp, "\n%d", array[i]);
        else
            fprintf(fp, " %d ", array[i]);
    }
    fclose(fp);

    printf("\n������Ҫ���ҵ�Ԫ��\n");
    int key;
    scanf("%d", &key);
    clock_t start = clock();
    int location = BinarySearch(array, 0, num - 1, key);        //����clock�����������Ժ�������ʱ��
    clock_t end = clock();
    if (location == -1)
        printf("����ʧ��\n");
    else
        printf("��Ԫ���������е�λ�ã�%d(���㿪ʼ)\n", location);
    printf("����ʱ��: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}

