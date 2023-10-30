/******************************************************
实验二：动态规划问题1.最优子结构2.重叠子问题
（1）找出最优解的性质，并刻画其结构特征
（2）递归地定义最优值
（3）以自底向上的方式计算最优值
（4）根据计算最优值时得到的信息构造最优解
二、最长公共子序列问题LCS
Q:给定两个序列X、Y，找出X和Y的最长公共子序列
INPUT：X={x1,x2,...,xm},Y={y1,y2,...,yn}
OUTPUT:X和Y的最长公共子序列Z
LI YANG 2021065408
2023.10.13
******************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>
using namespace std;

void LCSlength(int m,int n,char *x,char *y,int **c,int **b)
{	
	
	for (int i = 0; i <= m; i++)                //c[i][j]存储Xi和Yj的最长公共子序列的长度
		c[i][0] = 0;
	for (int i = 0; i <= n; i++)
		c[0][i] = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)            //b[i][j]记录c[i][j]的值是由哪个子问题的解得到的
		{
			if (x[i-1] == y[j-1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;

			}
			else if (c[i - 1][j] >= c[i][j - 1]) 
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;
			}
		}
	}
}

void LCS(int i, int j, char* x, int** b)         //打印出X和Y序列的最长公共子序列
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		LCS(i - 1, j - 1, x, b);
		std::cout << x[i-1];
	}
	else if (b[i][j] == 2)
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}

char generateRandomChar()         // 随机生成大写或小写字母
{
	char randomChar;
	int choice = rand() % 2;
	if (choice == 0)
		randomChar = 'A' + rand() % 26; 
	else 
		randomChar = 'a' + rand() % 26;

	return randomChar;
}

int main()
{

	int m, n;
	std::cout << "请输入第一个序列的长度: ";
	std::cin >> m;

	std::cout << "请输入第二个序列的长度: ";
	std::cin >> n;

	char* x = new char[m];
	char* y = new char[n];

	clock_t start = clock();          //利用clock（）函数计算花费时间
	srand(unsigned(time(0)));   // 使用当前时间作为随机数种子
	std::cout << "随机生成第一个序列: ";
	for (int i = 0; i < m; i++)
	{
		x[i] = generateRandomChar();
	}
	FILE* fp = fopen("X.txt", "w");           //可在‘X.txt’中查看数据
	for (int i = 0; i < m; i++)
	{
		if (i % 100 == 0)
		{
			fprintf(fp, "\n%c", x[i]);
		}
		else
		{
			fprintf(fp, " %c ", x[i]);
		}
	}
		fclose(fp);
		cout << "可在‘X.txt’中查看数据" << endl;

	std::cout << "随机生成第二个序列: ";
	for (int i = 0; i < n; i++)
	{
		y[i] = generateRandomChar();
	}
	fp = fopen("Y.txt", "w");           //可在‘Y.txt’中查看数据
	for (int i = 0; i < n; i++)
	{
			
		if (i % 100 == 0)
		{
			fprintf(fp, "\n%c", y[i]);
		}
		else
		{
			fprintf(fp, " %c ", y[i]);
		}
	}
	    fclose(fp);
		cout << "可在‘Y.txt’中查看数据" << endl;

		int** c = new int* [m + 1];
		int** b = new int* [m + 1];

		for (int i = 0; i <= m; i++)
		{
			c[i] = new int[n + 1];
			b[i] = new int[n + 1];
		}

		LCSlength(m, n, x, y, c, b);              // 调用LCSlength函数
		if (c[m][n] == 0)
		{
			std::cout << "X序列和Y序列不存在最长公共子序列 " << std::endl;
			return 0;
		}

		else
			std::cout << "最长公共子序列长度为: " << c[m][n] << std::endl; // 输出最长公共子序列的长度                         
		    std::cout << "最长公共子序列为: ";
		LCS(m, n, x, b);                                               // 调用LCS函数
		    std::cout << std::endl;                                    // 输出最长公共子序列

		clock_t end = clock();
		printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);
		for (int i = 0; i <= m; i++)                                   // 释放动态分配的内存
		{
			delete[] c[i];
			delete[] b[i];
		}
	    delete[] x;
		delete[] y;
		return 0;
}

