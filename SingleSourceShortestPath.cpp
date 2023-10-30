/******************************************************
实验五：分支限界法问题
1.队列式（FIFO）分支限界法2.优先队列式分支限界法
（1）常以广度优先或以最小耗费（最大效益）优先方式
 搜索问题的解空间树
（2）在分支限界法中，每一个活结点，只有一次机会成为扩展结点
 活结点一旦成为扩展结点，就一次性产生其所有儿子结点，在这些
 儿子结点中，导致不可行解或导致非最优解的儿子结点被舍弃。其余
 儿子结点被加入活结点表中。
（3）从活结点表中取下一结点成为当前扩展结点，重复上述过程至
 找到所需解或活结点表为空
二、单源最短路径问题SinglesourceNodeShortestPath
Q:给定一个带权有向图G=(V,E),其中每条边的权是非负实数。
给定V中的一个顶点称为源。计算从源节点到图中所有其他顶点的最短路径。
INPUT：一个有向图或无向图，表示为一组节点（或顶点）和边，
一个特定的源节点，从这个源节点开始计算最短路径，每条边的权重
OUTPUT:从源节点到图中每个其他节点的最短路径的长度，
从源节点到每个节点的实际路径，以便重建最短路径。
LI YANG 2021065408
2023.10.19
******************************************************/

#include <iostream>
#include <queue>
#include <limits>
#include <vector>

const int not_reachable = 99;   //定义的不可到达值
const int MAX = 20;            //顶点数的最大值 
   
struct Graph 
{
    int n;             // 图G的顶点数
    int c[MAX][MAX];   // 图G的邻接矩阵
};

struct MinHeapNode       //最小堆，便于寻找最短路径
{
    int i;              // 顶点编号
    int length;         // 当前路径长度

    bool operator>(const MinHeapNode& other) const
    {
        return length > other.length;
    }
};

bool Bound(int v, int dist[], int currentNode_dist)  // 如果当前路径长度已经大于节点v的最短路径长度，则执行剪枝（根节点）
{
    
    return dist[v] <= currentNode_dist;
}

void PrintPath(const std::vector<int>& prev, int sourceNode, int currentNode)  //递归调用自身，逐级打印出最短路径
{
    if (currentNode == sourceNode)
    {
        std::cout << currentNode;
    }
    else {
        PrintPath(prev, sourceNode, prev[currentNode]);
        std::cout << " -> " << currentNode;
    }
}

void ShortestPaths(const Graph& graph, int sourceNode)
{
    int n = graph.n;
    int dist[MAX];
    std::vector<int> prev(MAX, -1);         // 存储前驱顶点的数组

    std::priority_queue<MinHeapNode, std::vector<MinHeapNode>, std::greater<MinHeapNode>> priority_queue; // 优先队列用于最短路径搜索
    MinHeapNode E;
    E.i = sourceNode;
    E.length = 0;
    dist[sourceNode] = 0;
    priority_queue.push(E);              // 将源节点添加到队列中

    for (int i = 1; i <= n; i++) 
    {
        if (i != sourceNode) {
            dist[i] = not_reachable;          // 将其他节点的距离初始化为不可到达值
        }
    }

    while (!priority_queue.empty())
    {
        int u = priority_queue.top().i;
        int currentNode_dist = priority_queue.top().length;
        priority_queue.pop();

        if (currentNode_dist > dist[u]) 
        {
            continue;                    // 剪枝：如果当前路径长度大于已知的最短路径，跳过
        }

        for (int v = 1; v <= n; v++)   
        {
            if (graph.c[u][v] != not_reachable)
            {
                if (dist[u] + graph.c[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + graph.c[u][v];
                    prev[v] = u;           // 更新前驱节点
                    MinHeapNode N;
                    N.i = v;
                    N.length = dist[v];
                    priority_queue.push(N);
                }
            }
        }
    }

    
    for (int i = 1; i <= n; i++)        // 输出最短距离和路径
    {
        if (i != sourceNode)
        {
            std::cout << "从源节点 " << sourceNode << " 到顶点 " << i << " 的最短距离为: ";
            if (dist[i] == not_reachable) 
            {
                std::cout << "不可达" << std::endl;
            }
            else
            {
                std::cout << dist[i] << std::endl;
                std::cout << "最短路径: ";
                PrintPath(prev, sourceNode, i);
                std::cout << std::endl;
            }
        }
    }
}


int main() 
{
    int n; // 顶点数
    std::cout << "请输入图的顶点数: ";
    std::cin >> n;

    Graph graph;
    graph.n = n;

    std::cout << "请输入带权有向图的邻接矩阵 (使用 " << not_reachable << " 表示不可达):\n";  // 输入邻接矩阵
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cin >> graph.c[i][j];
        }
    }

    int sourceNode;
    std::cout << "请输入源节点: ";
    std::cin >> sourceNode;

    clock_t start = clock();          //利用clock（）函数计算花费时间
    ShortestPaths(graph, sourceNode);
    clock_t end = clock();
    printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);

    return 0;
}

