#include <bits/stdc++.h>

using namespace std;

// 课程表III
// 这里有n门不同的在线课程，按从1到n编号
// 给你一个数组courses
// 其中courses[i]=[durationi, lastDayi]表示第i门课将会持续上durationi天课
// 并且必须在不晚于lastDayi的时候完成
// 你的学期从第 1 天开始
// 且不能同时修读两门及两门以上的课程
// 返回你最多可以修读的课程数目
// 测试链接 : https://leetcode.cn/problems/course-schedule-iii/
class Solution
{
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 0: 代价, 1: 截止
		sort(courses.begin(), courses.end(), [](const auto& a, const auto& b)
		{
		  return a[1] < b[1];
		});

		// 大根堆
		priority_queue<int> heap;
		int time{};

		for (const auto& course : courses)
		{
			if (time + course[0] <= course[1])
			{
				heap.push(course[0]);
				time += course[0];
			}
			else
			{
				// time + c[0] > c[1]
				if (!heap.empty()
						&& heap.top() > course[0])
				{
					time += course[0] - heap.top();
					heap.pop();
					heap.push(course[0]);
				}
			}
		}

		return heap.size();
	}
};
