/******************************************************
ʵ�������̬�滮����1.�����ӽṹ2.�ص�������
��1���ҳ����Ž�����ʣ����̻���ṹ����
��2���ݹ�ض�������ֵ
��3�����Ե����ϵķ�ʽ��������ֵ
��4�����ݼ�������ֵʱ�õ�����Ϣ�������Ž�
һ��������������MatrixChain
Q:����n����������A[i]��A[i+1]�ɳˣ������n����������˻����������˴���
INPUT���������N
OUTPUT:n����������ټ��������ͨ�����ټ�������õ������ż������
LI YANG 2021065408
2023.10.13
******************************************************/

#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
#define N 300

void MatrixChain(int *p, int m[N + 1][N + 1], int s[N + 1][N + 1])    //�ݹ��㷨��������ֵ
{
    int n = N;
    for (int i = 1; i <= n; i++)                                    //���ȼ����m[i][i] =0
        m[i][i] = 0;
    for (int r = 2; r <= n; r++)                             //����������������ʽ���μ���m[i][i+1],m[i][i+2]......
    {
        for (int i = 1; i <= n - r + 1; i++)
        {
            int j = i + r - 1;
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];    
            s[i][j] = i;
            for (int k = i + 1; k < j; k++)                                //kΪ�ָ��
            {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];    //m[i][j]�ĵݹ鶨��
                if (t < m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}

void traceback(int i, int j, int s[][N + 1])            //ͨ������ֵ�������Ž�
{                                                       //s[i][j]�洢�Ͽ�λ��
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
    printf_s("��������������С�ڵ���300��:\n");
    scanf("%d", &n);

    clock_t start = clock();          //����clock�����������㻨��ʱ��
    std::srand(static_cast<unsigned>(std::time(nullptr)));     //�������������
    int total = 2 * n;
    std::vector<int> numbers;
    int FirstNum = rand() % (10) + 1;                          // �����������������ȡֵ��Χ��1��10
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
    FILE* fp = fopen("Matrix Line-Row.txt", "w");           //���ڡ�Matrix Line-Row.txt���в鿴����
        for (int i = 0; i < total; i++)
        {
            if (i % 2 == 0)
                fprintf(fp, "\n%d", C[i]);
            else
                fprintf(fp, " %d ", C[i]);
        }
        fclose(fp);
        printf_s("n������������������ɲ�����Matrix Line-Row.txt \n");

    for (int j = 1; j <= n - 1; j++)
        {
        p[j] = C[2 * j];
        }
        p[0] = C[0];
        p[n] = C[2 * n - 1];
        MatrixChain(p, m, s);
        printf_s("\n�����������ٴ���Ϊ\t%d\n", m[1][n]);
        printf_s("ͨ����������ֵ�õ��ľ����������Ž�Ϊ:\n\t\n");
        traceback(1, n, s);
        clock_t end = clock();
        printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
