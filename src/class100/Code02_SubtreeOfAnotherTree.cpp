#include <bits/stdc++.h>

using namespace std;

// 另一棵树的子树
// 给你两棵二叉树root和subRoot
// 检验root中是否包含和subRoot具有相同结构和节点值的子树
// 如果存在，返回true
// 否则，返回false
// 测试链接 : https://leetcode.cn/problems/subtree-of-another-tree/

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode()
			:val(0), left(nullptr), right(nullptr)
	{
	}

	TreeNode(int x)
			:val(x), left(nullptr), right(nullptr)
	{
	}

	TreeNode(int x, TreeNode* left, TreeNode* right)
			:val(x), left(left), right(right)
	{
	}
};

class Solution
{
public:
	// 二叉树先序序列化 + KMP算法匹配
	// 时间复杂度O(n + m)
	bool isSubtree(TreeNode* root, TreeNode* subRoot)
	{
		if (root && subRoot)
		{
			vector<string> s1, s2;
			serial(root, s1);
			serial(subRoot, s2);

			return kmp(s1, s2) != -1;
		}

		return !subRoot;
	}

	int kmp(vector<string>& s1, vector<string>& s2)
	{
		int n = s1.size(), m = s2.size(), x = 0, y = 0;
		vector<int> next = nextArray(s2);

		while (x < n && y < m)
		{
			if (s1[x] == s2[y])
			{
				++x, ++y;
			}
			else if (!y)
			{
				++x;
			}
			else
			{
				y = next[y];
			}
		}

		return y == m ? x - y : -1;
	}

	vector<int> nextArray(vector<string>& s)
	{
		int m = s.size();
		if (m == 1)
		{
			return { -1 };
		}

		vector<int> next(m);
		next[0] = -1;

		int i = 2, cn = 0;
		while (i < next.size())
		{
			if (s[i - 1] == s[cn])
			{
				next[i++] = ++cn;
			}
			else if (cn > 0)
			{
				cn = next[cn];
			}
			else
			{
				next[i++] = 0;
			}
		}

		return next;
	}

	void serial(TreeNode* head, vector<string>& path)
	{
		if (!head)
		{
			path.emplace_back("null");
		}
		else
		{
			path.push_back(to_string(head->val));
			serial(head->left, path);
			serial(head->right, path);
		}
	}
};
