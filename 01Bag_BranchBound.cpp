/******************************************************
ʵ���壺��֧�޽編����
1.����ʽ��FIFO����֧�޽編2.���ȶ���ʽ��֧�޽編
��1�����Թ�����Ȼ�����С�ķѣ����Ч�棩���ȷ�ʽ
 ��������Ľ�ռ���
��2���ڷ�֧�޽編�У�ÿһ�����㣬ֻ��һ�λ����Ϊ��չ���
 ����һ����Ϊ��չ��㣬��һ���Բ��������ж��ӽ�㣬����Щ
 ���ӽ���У����²����н���·����Ž�Ķ��ӽ�㱻����������
 ���ӽ�㱻����������
��3���ӻ������ȡ��һ����Ϊ��ǰ��չ��㣬�ظ�����������
 �ҵ�����������Ϊ��
һ��0-1��������01Bag_BranchBound
Q:����n����Ʒ��һ��������Ʒi������Ϊwi����ֵΪvi��
��������Ϊc�������ѡ��װ�뱳����Ʒʹ����Ʒ�ܼ�ֵ
����Ҳ�������������
INPUT��c>0,wi>0,vi>0,1<=i<=n
OUTPUT:(x1,x2,...,xn) xi=0/1
LI YANG 2021065408
2023.10.17
******************************************************/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Object       // ��Ʒ�Ľṹ�壬������������ֵ������
{    
    int weight;
    int value;
    int index;
};

struct Node     // ���ȶ��н��Ľṹ�壬�����㼶����ǰ�ۼƼ�ֵ����ǰ�ۼ��������Ͻ�
{
    int level;
    int c_value;
    int c_weight;
    double bound;
    std::vector<int> path;

    Node(int n) : path(n) {}          
                                          
    bool operator<(const Node& other) const        //����λ������ֵ��Ϊ�б����ȼ�����  
    {
        return bound < other.bound;
    }
};

double Bound(const Node& u, const std::vector<Object>& objects, int n, int capacity)   
{                    // ����ڵ�������Ͻ磨bound��
    if (u.c_weight >= capacity)
    {
        return 0.0;
    }

    double bound = u.c_value;
    int j = u.level + 1;
    int totalWeight = u.c_weight;

    while (j < n && totalWeight + objects[j].weight <= capacity) 
    {
        totalWeight += objects[j].weight;
        bound += objects[j].value;
        j++;
    }

    if (j < n) 
    {               //ѡ����и����Ͻ�Ľڵ�
        bound += (capacity - totalWeight) * (static_cast<double>(objects[j].value) / objects[j].weight);
    }

    return bound;
}

int BranchBound(const std::vector<Object>& objects, int capacity, std::vector<int>& bestx)
{               // ��֧�޽編���0/1��������
    int n = objects.size(); 
    std::priority_queue<Node> priority_queue;

    Node u(n);               //��ǰ��չ�ڵ�u

    u.level = -1;
    u.c_value = u.c_weight = 0;
    u.bound = Bound(u, objects, n, capacity);

    int maxValue = 0;

    priority_queue.push(u);

    while (!priority_queue.empty())
    {
        u = priority_queue.top();
        priority_queue.pop();

        if (u.bound > maxValue) 
        {
            u.level++;
            if (u.level < n)              
            {
                int nextItemIndex = u.level;

                u.c_weight += objects[nextItemIndex].weight;
                u.c_value += objects[nextItemIndex].value;
                u.path[nextItemIndex] = 1;

                if (u.c_weight <= capacity && u.c_value > maxValue)    //ѡ��ڵ�u
                {
                    maxValue = u.c_value;
                    bestx = u.path;
                }

                u.bound = Bound(u, objects, n, capacity);
                if (u.bound > maxValue) 
                {
                    priority_queue.push(u);
                }

                u.c_weight -= objects[nextItemIndex].weight;           //��ѡ��ڵ�u
                u.c_value -= objects[nextItemIndex].value;
                u.path[nextItemIndex] = 0;

                u.bound = Bound(u, objects, n, capacity);
                if (u.bound > maxValue)
                {
                    priority_queue.push(u);
                }
            }
        }
    }

    return maxValue;
}

int main() 
{
    int n; // ��Ʒ����
    int c; // ��������

    std::cout << "��������Ʒ������";
    std::cin >> n;
    std::cout << "�����뱳��������";
    std::cin >> c;

    std::vector<Object> objects(n);

    for (int i = 0; i < n; i++) 
    {
        std::cout << "������� " << i + 1 << " ����Ʒ�������ͼ�ֵ��";
        std::cin >> objects[i].weight >> objects[i].value;
        objects[i].index = i;
    }

    std::sort(objects.begin(), objects.end(), [](const Object& a, const Object& b)
        {
        return static_cast<double>(a.value) / a.weight > static_cast<double>(b.value) / b.weight;
        });

    std::vector<int> bestx(n, 0);
    clock_t start = clock();          //����clock�����������㻨��ʱ��
    int maxValue = BranchBound(objects, c, bestx);

    std::cout << "��װ�뱳����Ʒ������ܼ�ֵΪ��" << maxValue << std::endl;
    std::cout << "���뱳������Ʒ���Ϊ: ";
    std::vector<int> selectedItems;
    for (int i = 0; i < n; i++)
    {
        if (bestx[i] == 1) 
        {
            selectedItems.push_back(objects[i].index + 1);
        }
    }
    std::sort(selectedItems.begin(), selectedItems.end());  // ����С����˳������
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        std::cout << selectedItems[i] << " ";
    }
    std::cout << std::endl;

    clock_t end = clock();
    printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);
    system("pause");
    return 0;
}
