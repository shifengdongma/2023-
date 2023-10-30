/******************************************************
ʵ���ģ����ݷ�����1.��֦����2.��ռ�
��1������������⣬��������Ľ�ռ�
��2��ȷ�����������Ľ�ռ�ṹ
��3����������ȷ�ʽ������ռ䣬��������������
     �ü�֦����������Ч����
 ���ü�֦������Լ���������޽纯��
һ��0-1��������01Bag_BackTrack
Q:����n����Ʒ��һ��������Ʒi������Ϊwi����ֵΪvi��
��������Ϊc�������ѡ��װ�뱳����Ʒʹ����Ʒ�ܼ�ֵ
����Ҳ�������������
INPUT��c>0,wi>0,vi>0,1<=i<=n
OUTPUT:(x1,x2,...,xn) xi=0/1
LI YANG 2021065408
2023.10.16
******************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
double c;
double v[100];
double w[100];
double cw = 0.0;             //��ǰ��Ʒ����
double cv = 0.0;             //��ǰ��Ʒ��ֵ
double bestv = 0.0;          //��ǰ���ż�ֵ
double ratio[100];           //��Ʒ��λ�����ļ�ֵ
int order[100];
int choose[100];

void knapsort()                                 //����λ������ֵ�������� 
{
    for (int i = 1; i <= n; i++)
    {
        ratio[i] = v[i] / w[i];
    }
    for (int i = 1; i <= n - 1; i++) 
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (ratio[i] < ratio[j])          // ������ֵ��˳�򡢼�ֵ������
            {
                swap(ratio[i], ratio[j]);    
                swap(order[i], order[j]);
                swap(v[i], v[j]);
                swap(w[i], w[j]);
            }
        }
    }
}

double bound(int i)               //�޽纯���������Ͻ�
{
    double leftw = c - cw;        //ʣ������
    double upvalue = cv;
    while (i <= n && w[i] <= leftw)
    {
        leftw -= w[i];
        upvalue += v[i];
        i++;
    }
    if (i <= n)                   //װ������
    {
        upvalue += v[i] / w[i] * leftw;
    }
    return upvalue;             //���ص�ǰ����Ͻ�
}

void backtrack(int i)          //���ݷ��������нڵ�
{
    if (i > n)                 //����Ҷ�ڵ�
    {
        bestv = cv;
        return;
    }

    if (cw + w[i] <= c)        //����������
    {
        cw += w[i];            //ѡ����������Ʒ�����µ�ǰ��������ֵ
        cv += v[i];
        choose[i] = 1;
        backtrack(i + 1);      //ȡ��������ѡ�񣬻��ݲ�׼������������
        cw -= w[i];
        cv -= v[i];
    }
    if (bound(i + 1) > bestv)   //��֦�������жϽ����������ܷ��ҵ����õĽ�
    {
        backtrack(i + 1);
    }

}

int main()
{
    cout << "��������Ʒ����������������";
    cin >> n >> c;

    
    for (int i = 1; i <= n; i++)
    {
        cout << "�������" << i << "����Ʒ�����ͼ�ֵ��";
        cin >> w[i] >> v[i];
        order[i] = i;          // ��¼��Ʒ��˳��
    }
    clock_t start = clock();          //����clock�����������㻨��ʱ��
    knapsort();
    backtrack(1);

    vector<int> selectedItems;   // ����һ��װ�뱳������Ʒ�������
    for (int i = 1; i <= n; i++)
    {
        if (choose[i] == 1)
        {
            selectedItems.push_back(order[i]);
        }
    }

    sort(selectedItems.begin(), selectedItems.end());  // ��װ�뱳������Ʒ��Ž�������

    cout << "��װ�뱳����Ʒ������ܼ�ֵΪ��" << bestv << endl;
    cout << "���뱳������Ʒ���Ϊ��";
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        cout << selectedItems[i] << " ";
    }
    cout << endl;
    clock_t end = clock();
    printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
