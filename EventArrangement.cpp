/******************************************************
ʵ������̰���㷨����1.�����ӽṹ����2.̰��ѡ������
��1��һ���������Ž�������������Ž�
��2�������������Ž���һϵ�оֲ����Ž�ѡ��
�Զ����£�ÿһ��̰��ѡ�������Ϊ������
һ�����������EventArrangement
Q:����n�������E={1,2,3,...,n},ÿ���ʹ��ͬһ��Դ��
ͬһʱ��ֻ��һ�����ʹ�ø���Դ������ѡ��������ݻ�Ӽ���
INPUT��S={1,2,3,...,n} F={[si,fi]} 1<= i <=n
OUTPUT:S��������ݼ���
LI YANG 2021065408
2023.10.14
******************************************************/
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Activity           // �����ṹ��
{
	int start_time;
	int end_time;
};

bool comparing(const Activity& a1, const Activity& a2)    // �ȽϺ��������ڰ�����ʱ������
{
	return a1.end_time < a2.end_time;
}

void EventArrangement(std::vector<Activity>& activities)    // ̰���㷨������������ĺ���
{
	int n = activities.size();
	std::sort(activities.begin(), activities.end(), comparing); // ������ʱ��Ի��������

	int prevend_timeTime = activities[0].end_time;   // ��ʼ����һ������ʱ��������ѡ��
	std::cout << "ѡ��Ļ���1";
	
	for (int i = 1; i < n; i++)                       // �ӵڶ������ʼ����
	{
		if (activities[i].start_time >= prevend_timeTime)  // ѡ��
		{
			std::cout << ", �" << i + 1;
			prevend_timeTime = activities[i].end_time;
		}
	}
	std::cout << std::endl;
}

int main()
{
	int n;
	std::cout << "�����뼯���л������: ";
	std::cin >> n;
	
	std::vector<Activity> activities(n);
	std::cout << "��ֱ�����ÿ����Ŀ�ʼʱ��ͽ���ʱ��" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cin >> activities[i].start_time >> activities[i].end_time;
	}
	clock_t start = clock();          //����clock�����������㻨��ʱ��
	EventArrangement(activities);    // ����̰���㷨������������������
	clock_t end = clock();
	printf_s("\n����ʱ��Ϊ��%lf\n", double(end - start) / CLOCKS_PER_SEC);
	return 0;
}
