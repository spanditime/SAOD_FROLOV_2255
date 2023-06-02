#pragma once
#include <string>
#include <cstring>

class KMP
{
	static int* pref;
public:
	KMP() = delete;
	static int SubFind(const char* subs, const char* s)
	{
		delete[] pref;
		auto s_size = strlen(s);
		auto sub_size = strlen(subs);
		pref = new int[sub_size + s_size];
		pref[0] = 0;
		int k = 0;
		for (int i = 1; i < sub_size; i++)
		{
			if (subs[k] == subs[i])
			{
				k++;
				pref[i] = k;
			}
			else
			{
				if (i != 0 && pref[i - 1] != 0)
				{
					pref[i] = pref[pref[i - 1] - 1];
					if (subs[pref[i]] == subs[i]) pref[i]++;
					k = pref[i];
				}
				else
				{
					k = 0;
					pref[i] = 0;
				}
			}
		}
		k = 0;
		for (auto i = 0; i < s_size; i++)
		{
			int delta = i + sub_size;
			if (k != sub_size)
			{
				if (subs[k] == s[i])
				{
					k++;
					pref[delta] = k;
				}
				else
				{
					if (pref[delta - 1] != 0)
					{
						pref[delta] = pref[pref[delta - 1] - 1];
						if (subs[pref[delta]] == s[i]) pref[delta]++;
						k = pref[delta];
					}
					else
					{
						k = 0;
						pref[delta] = 0;
					}
				}
			}
			else return i - sub_size;
		}
		//pref[sub_size + s_size] = -1;
		return -1;
	}
	static void clear()
	{
		delete[] pref;
	}
	~KMP()
	{
		delete[] pref;
	}
};