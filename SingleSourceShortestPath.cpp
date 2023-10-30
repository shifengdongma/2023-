/******************************************************
ʵ���壺��֧�޽編����
1.����ʽ��FIFO����֧�޽編2.���ȶ���ʽ��֧�޽編
��1�����Թ�����Ȼ�����С�ķѣ����Ч�棩���ȷ�ʽ
 ��������Ľ�ռ���
��2���ڷ�֧�޽編�У�ÿһ�����㣬ֻ��һ�λ����Ϊ��չ���
 ����һ����Ϊ��չ��㣬��һ���Բ��������ж��ӽ�㣬����Щ
 ���ӽ���У����²����н���·����Ž�Ķ��ӽ�㱻����������
 ���ӽ�㱻���������С�
��3���ӻ������ȡ��һ����Ϊ��ǰ��չ��㣬�ظ�����������
 �ҵ�����������Ϊ��
������Դ���·������SinglesourceNodeShortestPath
Q:����һ����Ȩ����ͼG=(V,E),����ÿ���ߵ�Ȩ�ǷǸ�ʵ����
����V�е�һ�������ΪԴ�������Դ�ڵ㵽ͼ������������������·����
INPUT��һ������ͼ������ͼ����ʾΪһ��ڵ㣨�򶥵㣩�ͱߣ�
һ���ض���Դ�ڵ㣬�����Դ�ڵ㿪ʼ�������·����ÿ���ߵ�Ȩ��
OUTPUT:��Դ�ڵ㵽ͼ��ÿ�������ڵ�����·���ĳ��ȣ�
��Դ�ڵ㵽ÿ���ڵ��ʵ��·�����Ա��ؽ����·����
LI YANG 2021065408
2023.10.19
******************************************************/

#include <iostream>
#include <queue>
#include <limits>
#include <vector>

const int not_reachable = 99;   //����Ĳ��ɵ���ֵ
const int MAX = 20;            //�����������ֵ 
   
struct Graph 
{
    int n;             // ͼG�Ķ�����
    int c[MAX][MAX];   // ͼG���ڽӾ���
};

struct MinHeapNode       //��С�ѣ�����Ѱ�����·��
{
    int i;              // ������
    int length;         // ��ǰ·������

    bool operator>(const MinHeapNode& other) const
    {
        return length > other.length;
    }
};

bool Bound(int v, int dist[], int currentNode_dist)  // �����ǰ·�������Ѿ����ڽڵ�v�����·�����ȣ���ִ�м�֦�����ڵ㣩
{
    
    return dist[v] <= currentNode_dist;
}

void PrintPath(const std::vector<int>& prev, int sourceNode, int currentNode)  //�ݹ���������𼶴�ӡ�����·��
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
    std::vector<int> prev(MAX, -1);         // �洢ǰ�����������

    std::priority_queue<MinHeapNode, std::vector<MinHeapNode>, std::greater<MinHeapNode>> priority_queue; // ���ȶ����������·������
    MinHeapNode E;
    E.i = sourceNode;
    E.length = 0;
    dist[sourceNode] = 0;
    priority_queue.push(E);              // ��Դ�ڵ���ӵ�������

    for (int i = 1; i <= n; i++) 
    {
        if (i != sourceNode) {
            dist[i] = not_reachable;          // �������ڵ�ľ����ʼ��Ϊ���ɵ���ֵ
        }
    }

    while (!priority_queue.empty())
    {
        int u = priority_queue.top().i;
        int currentNode_dist = priority_queue.top().length;
        priority_queue.pop();

        if (currentNode_dist > dist[u]) 
        {
            continue;                    // ��֦�������ǰ·�����ȴ�����֪�����·��������
        }

        for (int v = 1; v <= n; v++)   
        {
            if (graph.c[u][v] != not_reachable)
            {
                if (dist[u] + graph.c[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + graph.c[u][v];
                    prev[v] = u;           // ����ǰ���ڵ�
                    MinHeapNode N;
                    N.i = v;
                    N.length = dist[v];
                    priority_queue.push(N);
                }
            }
        }
    }

    
    for (int i = 1; i <= n; i++)        // �����̾����·��
    {
        if (i != sourceNode)
        {
            std::cout << "��Դ�ڵ� " << sourceNode << " ������ " << i << " ����̾���Ϊ: ";
            if (dist[i] == not_reachable) 
            {
                std::cout << "���ɴ�" << std::endl;
            }
            else
            {
                std::cout << dist[i] << std::endl;
                std::cout << "���·��: ";
                PrintPath(prev, sourceNode, i);
                std::cout << std::endl;
            }
        }
    }
}


int main() 
{
    int n; // ������
    std::cout << "������ͼ�Ķ�����: ";
    std::cin >> n;

    Graph graph;
    graph.n = n;

    std::cout << "�������Ȩ����ͼ���ڽӾ��� (ʹ�� " << not_reachable << " ��ʾ���ɴ�):\n";  // �����ڽӾ���
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cin >> graph.c[i][j];
        }
    }

    int sourceNode;
    std::cout << "������Դ�ڵ�: ";
    std::cin >> sourceNode;

    clock_t start = clock();          //����clock�����������㻨��ʱ��
    ShortestPaths(graph, sourceNode);
    clock_t end = clock();
    printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);

    return 0;
}

