/******************************************************
实验三：贪心算法问题1.最优子结构性质2.贪心选择性质
（1）一个问题最优解包含子问题最优解
（2）问题整体最优解由一系列局部最优解选择，
自顶向下，每一次贪心选择将问题简化为子问题
一、活动安排问题EventArrangement
Q:给定n个活动集合E={1,2,3,...,n},每个活动使用同一资源，
同一时间只有一个活动能使用该资源，从中选出最大相容活动子集合
INPUT：S={1,2,3,...,n} F={[si,fi]} 1<= i <=n
OUTPUT:S的最大相容集合
LI YANG 2021065408
2023.10.14
******************************************************/
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Activity           // 定义活动结构体
{
	int start_time;
	int end_time;
};

bool comparing(const Activity& a1, const Activity& a2)    // 比较函数，用于按结束时间排序活动
{
	return a1.end_time < a2.end_time;
}

void EventArrangement(std::vector<Activity>& activities)    // 贪心算法解决活动安排问题的函数
{
	int n = activities.size();
	std::sort(activities.begin(), activities.end(), comparing); // 按结束时间对活动进行排序

	int prevend_timeTime = activities[0].end_time;   // 初始化第一个结束时间最早活动被选择
	std::cout << "选择的活动：活动1";
	
	for (int i = 1; i < n; i++)                       // 从第二个活动开始遍历
	{
		if (activities[i].start_time >= prevend_timeTime)  // 选择活动
		{
			std::cout << ", 活动" << i + 1;
			prevend_timeTime = activities[i].end_time;
		}
	}
	std::cout << std::endl;
}

int main()
{
	int n;
	std::cout << "请输入集合中活动总数量: ";
	std::cin >> n;
	
	std::vector<Activity> activities(n);
	std::cout << "请分别输入每个活动的开始时间和结束时间" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cin >> activities[i].start_time >> activities[i].end_time;
	}
	clock_t start = clock();          //利用clock（）函数计算花费时间
	EventArrangement(activities);    // 调用贪心算法函数来解决活动安排问题
	clock_t end = clock();
	printf_s("\n花费时间为：%lf\n", double(end - start) / CLOCKS_PER_SEC);
	return 0;
}
