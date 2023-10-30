/******************************************************
ʵ�������̬�滮����1.�����ӽṹ2.�ص�������
��1���ҳ����Ž�����ʣ����̻���ṹ����
��2���ݹ�ض�������ֵ
��3�����Ե����ϵķ�ʽ��������ֵ
��4�����ݼ�������ֵʱ�õ�����Ϣ�������Ž�
�������������������LCS
Q:������������X��Y���ҳ�X��Y�������������
INPUT��X={x1,x2,...,xm},Y={y1,y2,...,yn}
OUTPUT:X��Y�������������Z
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
	
	for (int i = 0; i <= m; i++)                //c[i][j]�洢Xi��Yj������������еĳ���
		c[i][0] = 0;
	for (int i = 0; i <= n; i++)
		c[0][i] = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)            //b[i][j]��¼c[i][j]��ֵ�����ĸ�������Ľ�õ���
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

void LCS(int i, int j, char* x, int** b)         //��ӡ��X��Y���е������������
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

char generateRandomChar()         // ������ɴ�д��Сд��ĸ
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
	std::cout << "�������һ�����еĳ���: ";
	std::cin >> m;

	std::cout << "������ڶ������еĳ���: ";
	std::cin >> n;

	char* x = new char[m];
	char* y = new char[n];

	clock_t start = clock();          //����clock�����������㻨��ʱ��
	srand(unsigned(time(0)));   // ʹ�õ�ǰʱ����Ϊ���������
	std::cout << "������ɵ�һ������: ";
	for (int i = 0; i < m; i++)
	{
		x[i] = generateRandomChar();
	}
	FILE* fp = fopen("X.txt", "w");           //���ڡ�X.txt���в鿴����
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
		cout << "���ڡ�X.txt���в鿴����" << endl;

	std::cout << "������ɵڶ�������: ";
	for (int i = 0; i < n; i++)
	{
		y[i] = generateRandomChar();
	}
	fp = fopen("Y.txt", "w");           //���ڡ�Y.txt���в鿴����
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
		cout << "���ڡ�Y.txt���в鿴����" << endl;

		int** c = new int* [m + 1];
		int** b = new int* [m + 1];

		for (int i = 0; i <= m; i++)
		{
			c[i] = new int[n + 1];
			b[i] = new int[n + 1];
		}

		LCSlength(m, n, x, y, c, b);              // ����LCSlength����
		if (c[m][n] == 0)
		{
			std::cout << "X���к�Y���в���������������� " << std::endl;
			return 0;
		}

		else
			std::cout << "����������г���Ϊ: " << c[m][n] << std::endl; // �������������еĳ���                         
		    std::cout << "�����������Ϊ: ";
		LCS(m, n, x, b);                                               // ����LCS����
		    std::cout << std::endl;                                    // ��������������

		clock_t end = clock();
		printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);
		for (int i = 0; i <= m; i++)                                   // �ͷŶ�̬������ڴ�
		{
			delete[] c[i];
			delete[] b[i];
		}
	    delete[] x;
		delete[] y;
		return 0;
}

