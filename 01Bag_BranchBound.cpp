/******************************************************
实验五：分支限界法问题
1.队列式（FIFO）分支限界法2.优先队列式分支限界法
（1）常以广度优先或以最小耗费（最大效益）优先方式
 搜索问题的解空间树
（2）在分支限界法中，每一个活结点，只有一次机会成为扩展结点
 活结点一旦成为扩展结点，就一次性产生其所有儿子结点，在这些
 儿子结点中，导致不可行解或导致非最优解的儿子结点被舍弃，其余
 儿子结点被加入活结点表中
（3）从活结点表中取下一结点成为当前扩展结点，重复上述过程至
 找到所需解或活结点表为空
一、0-1背包问题01Bag_BranchBound
Q:给定n种物品和一背包，物品i的重量为wi，价值为vi，
背包容量为c，该如何选择装入背包物品使得物品总价值
最大且不超过背包容量
INPUT：c>0,wi>0,vi>0,1<=i<=n
OUTPUT:(x1,x2,...,xn) xi=0/1
LI YANG 2021065408
2023.10.17
******************************************************/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Object       // 物品的结构体，包括重量、价值、索引
{    
    int weight;
    int value;
    int index;
};

struct Node     // 优先队列结点的结构体，包括层级、当前累计价值、当前累计重量和上界
{
    int level;
    int c_value;
    int c_weight;
    double bound;
    std::vector<int> path;

    Node(int n) : path(n) {}          
                                          
    bool operator<(const Node& other) const        //将单位重量价值作为判别优先级依据  
    {
        return bound < other.bound;
    }
};

double Bound(const Node& u, const std::vector<Object>& objects, int n, int capacity)   
{                    // 计算节点的最优上界（bound）
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
    {               //选择具有更高上界的节点
        bound += (capacity - totalWeight) * (static_cast<double>(objects[j].value) / objects[j].weight);
    }

    return bound;
}

int BranchBound(const std::vector<Object>& objects, int capacity, std::vector<int>& bestx)
{               // 分支限界法求解0/1背包问题
    int n = objects.size(); 
    std::priority_queue<Node> priority_queue;

    Node u(n);               //当前扩展节点u

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

                if (u.c_weight <= capacity && u.c_value > maxValue)    //选择节点u
                {
                    maxValue = u.c_value;
                    bestx = u.path;
                }

                u.bound = Bound(u, objects, n, capacity);
                if (u.bound > maxValue) 
                {
                    priority_queue.push(u);
                }

                u.c_weight -= objects[nextItemIndex].weight;           //不选择节点u
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
    int n; // 物品数量
    int c; // 背包容量

    std::cout << "请输入物品数量：";
    std::cin >> n;
    std::cout << "请输入背包容量：";
    std::cin >> c;

    std::vector<Object> objects(n);

    for (int i = 0; i < n; i++) 
    {
        std::cout << "请输入第 " << i + 1 << " 个物品的重量和价值：";
        std::cin >> objects[i].weight >> objects[i].value;
        objects[i].index = i;
    }

    std::sort(objects.begin(), objects.end(), [](const Object& a, const Object& b)
        {
        return static_cast<double>(a.value) / a.weight > static_cast<double>(b.value) / b.weight;
        });

    std::vector<int> bestx(n, 0);
    clock_t start = clock();          //利用clock（）函数计算花费时间
    int maxValue = BranchBound(objects, c, bestx);

    std::cout << "可装入背包物品的最大总价值为：" << maxValue << std::endl;
    std::cout << "放入背包的物品编号为: ";
    std::vector<int> selectedItems;
    for (int i = 0; i < n; i++)
    {
        if (bestx[i] == 1) 
        {
            selectedItems.push_back(objects[i].index + 1);
        }
    }
    std::sort(selectedItems.begin(), selectedItems.end());  // 按从小到大顺序排序
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        std::cout << selectedItems[i] << " ";
    }
    std::cout << std::endl;

    clock_t end = clock();
    printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);
    system("pause");
    return 0;
}
