#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

class BM
{
	static std::vector<int> b;
public:
	static int SubFind(const char* sub, const char* str)
	{
		int m = strlen(sub), n = strlen(str);
		CreateDictionary(sub, m);
		int s = 0;
		while (s <= n - m)
		{
			int j = m - 1;
			while (j >= 0 && sub[j] == str[s + j])
			{
				j--;
			}
			if (j < 0) return s;
			else s += std::max(1, j - b[str[s + j]]);
		}
	}
	static std::vector<int> Dict()
	{
		return b;
	}
private:
	static void CreateDictionary(const char* sub, int m)
	{
		for (int i = 0; i < m; i++)
			b[int(sub[i])] = i;
	}
};
