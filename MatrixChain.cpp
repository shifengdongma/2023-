/******************************************************
实验二：动态规划问题1.最优子结构2.重叠子问题
（1）找出最优解的性质，并刻画其结构特征
（2）递归地定义最优值
（3）以自底向上的方式计算最优值
（4）根据计算最优值时得到的信息构造最优解
一、矩阵连乘问题MatrixChain
Q:给定n个矩阵，其中A[i]与A[i+1]可乘，求计算n个矩阵的连乘积的最优连乘次数
INPUT：矩阵个数N
OUTPUT:n个矩阵的最少计算次数和通过最少计算次数得到的最优计算次序
LI YANG 2021065408
2023.10.13
******************************************************/

#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
#define N 300

void MatrixChain(int *p, int m[N + 1][N + 1], int s[N + 1][N + 1])    //递归算法计算最优值
{
    int n = N;
    for (int i = 1; i <= n; i++)                                    //首先计算出m[i][i] =0
        m[i][i] = 0;
    for (int r = 2; r <= n; r++)                             //按矩阵链长递增方式依次计算m[i][i+1],m[i][i+2]......
    {
        for (int i = 1; i <= n - r + 1; i++)
        {
            int j = i + r - 1;
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];    
            s[i][j] = i;
            for (int k = i + 1; k < j; k++)                                //k为分割点
            {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];    //m[i][j]的递归定义
                if (t < m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}

void traceback(int i, int j, int s[][N + 1])            //通过最优值构造最优解
{                                                       //s[i][j]存储断开位置
    if (i == j)
    {
        printf_s("A%d", i);
    }
    else
    {
        printf_s("(");
        traceback(i, s[i][j], s);
        traceback(s[i][j] + 1, j, s);
        printf_s(")");
    }
}

int main()
{
    int n;
    int p[N + 1];
    int m[N + 1][N + 1];
    int s[N + 1][N + 1];
    printf_s("请输入矩阵个数（小于等于300）:\n");
    scanf("%d", &n);

    clock_t start = clock();          //利用clock（）函数计算花费时间
    std::srand(static_cast<unsigned>(std::time(nullptr)));     //随机生成数程序
    int total = 2 * n;
    std::vector<int> numbers;
    int FirstNum = rand() % (10) + 1;                          // 生成随机整数，这里取值范围是1到10
    numbers.push_back(FirstNum);
    for (int i = 1; i <= total / 2; ++i)
        {  
             int random =rand() % (9) + 2;                  
             numbers.push_back(random);
             numbers.push_back(random);
        }
    int C[2 * N];
    for (int i = 0; i < total; ++i) {
        C[i] = numbers[i];
    }
    FILE* fp = fopen("Matrix Line-Row.txt", "w");           //可在‘Matrix Line-Row.txt’中查看数据
        for (int i = 0; i < total; i++)
        {
            if (i % 2 == 0)
                fprintf(fp, "\n%d", C[i]);
            else
                fprintf(fp, " %d ", C[i]);
        }
        fclose(fp);
        printf_s("n个矩阵的行列数已生成并存入Matrix Line-Row.txt \n");

    for (int j = 1; j <= n - 1; j++)
        {
        p[j] = C[2 * j];
        }
        p[0] = C[0];
        p[n] = C[2 * n - 1];
        MatrixChain(p, m, s);
        printf_s("\n矩阵连乘最少次数为\t%d\n", m[1][n]);
        printf_s("通过计算最优值得到的矩阵连乘最优解为:\n\t\n");
        traceback(1, n, s);
        clock_t end = clock();
        printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
