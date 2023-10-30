/******************************************************
实验四：回溯法问题1.剪枝函数2.解空间
（1）针对所给问题，定义问题的解空间
（2）确定易于搜索的解空间结构
（3）以深度优先方式搜索解空间，并在搜索过程中
     用剪枝函数避免无效搜索
 常用剪枝函数：约束函数，限界函数
一、0-1背包问题01Bag_BackTrack
Q:给定n种物品和一背包，物品i的重量为wi，价值为vi，
背包容量为c，该如何选择装入背包物品使得物品总价值
最大且不超过背包容量
INPUT：c>0,wi>0,vi>0,1<=i<=n
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
double cw = 0.0;             //当前物品重量
double cv = 0.0;             //当前物品价值
double bestv = 0.0;          //当前最优价值
double ratio[100];           //物品单位重量的价值
int order[100];
int choose[100];

void knapsort()                                 //按单位重量价值进行排序 
{
    for (int i = 1; i <= n; i++)
    {
        ratio[i] = v[i] / w[i];
    }
    for (int i = 1; i <= n - 1; i++) 
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (ratio[i] < ratio[j])          // 交换比值、顺序、价值、重量
            {
                swap(ratio[i], ratio[j]);    
                swap(order[i], order[j]);
                swap(v[i], v[j]);
                swap(w[i], w[j]);
            }
        }
    }
}

double bound(int i)               //限界函数，计算上界
{
    double leftw = c - cw;        //剩余容量
    double upvalue = cv;
    while (i <= n && w[i] <= leftw)
    {
        leftw -= w[i];
        upvalue += v[i];
        i++;
    }
    if (i <= n)                   //装满背包
    {
        upvalue += v[i] / w[i] * leftw;
    }
    return upvalue;             //返回当前最大上界
}

void backtrack(int i)          //回溯法遍历所有节点
{
    if (i > n)                 //到达叶节点
    {
        bestv = cv;
        return;
    }

    if (cw + w[i] <= c)        //进入左子树
    {
        cw += w[i];            //选择左子树物品，更新当前重量，价值
        cv += v[i];
        choose[i] = 1;
        backtrack(i + 1);      //取消左子树选择，回溯并准备遍历右子树
        cw -= w[i];
        cv -= v[i];
    }
    if (bound(i + 1) > bestv)   //剪枝操作，判断进入右子树能否找到更好的解
    {
        backtrack(i + 1);
    }

}

int main()
{
    cout << "请输入物品数量及背包容量：";
    cin >> n >> c;

    
    for (int i = 1; i <= n; i++)
    {
        cout << "请输入第" << i << "件物品重量和价值：";
        cin >> w[i] >> v[i];
        order[i] = i;          // 记录物品的顺序
    }
    clock_t start = clock();          //利用clock（）函数计算花费时间
    knapsort();
    backtrack(1);

    vector<int> selectedItems;   // 创建一个装入背包的物品编号数组
    for (int i = 1; i <= n; i++)
    {
        if (choose[i] == 1)
        {
            selectedItems.push_back(order[i]);
        }
    }

    sort(selectedItems.begin(), selectedItems.end());  // 对装入背包的物品编号进行排序

    cout << "可装入背包物品的最大总价值为：" << bestv << endl;
    cout << "放入背包的物品编号为：";
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        cout << selectedItems[i] << " ";
    }
    cout << endl;
    clock_t end = clock();
    printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
