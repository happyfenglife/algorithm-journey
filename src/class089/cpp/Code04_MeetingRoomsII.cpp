#include <bits/stdc++.h>

using namespace std;

// 会议室II
// 给你一个会议时间安排的数组 intervals
// 每个会议时间都会包括开始和结束的时间intervals[i]=[starti, endi]
// 返回所需会议室的最小数量
// 测试链接 : https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
int minMeetingRooms(vector<vector<int>>& meeting)
{
	int n = meeting.size();
	sort(meeting.begin(), meeting.end(), [](const auto& a, const auto& b)
	{
	  return a[0] < b[0];
	});

	priority_queue<int, vector<int>, greater<>> heap;
	int ans{};
	for (int i = 0; i < n; ++i)
	{
		while (!heap.empty()
				&& heap.top() <= meeting[i][0])
		{
			heap.pop();
		}

		heap.push(meeting[i][1]);
		ans = max(ans, (int)heap.size());
	}

	return ans;
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	while (cin >> N)
	{
		vector<vector<int>> meeting(N, vector<int>(2));
		for (int i = 0; i < N; ++i)
		{
			cin >> meeting[i][0] >> meeting[i][1];
		}

		cout << minMeetingRooms(meeting) << endl;
	}

	return 0;
}
