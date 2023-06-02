#include <iostream>
#include "kmp.hpp"
#include "bm.hpp"
#include "../BoxPlot-Timer/Timer.hpp"
#include <fstream>
#include <string>

int naive(const char* subs, const char* s)
{
	int s_size = strlen(s);
	int sub_size = strlen(subs);
	int found = 0;
	for (int i = 0; i < s_size; i++)
	{
		if (s[i] == subs[found]) found++;
			else found = 0;
		if (found == sub_size)
			return i - sub_size + 1;
	}
	return -1;
}

std::vector<int> prefix_function (const std::string& s) 
{
	size_t n = s.length();
	std::vector<int> pi(n); 
	for (size_t i=1; i<n; ++i) 
	{
		size_t j = pi[i-1];
		while ((j > 0) && (s[i] != s[j]))
			j = pi[j-1];
		if (s[i] == s[j]) 
		++j;
		pi[i] = j;
	}
	return pi;
} 

size_t kmp(const std::string& str, const std::string& sub)
{
	size_t l = sub.size();
	size_t* pi = new size_t[l];
	pi[0] = 0;
	for (int i  = 1;i < l ; ++i)
	{
		size_t j = pi[i - 1];
		while ((j > 0) && (sub[i] != sub[j]))
			j = pi[j - 1];
		if (sub[i] == sub[j])
		++j;
		pi[i] = j;
	}
	size_t j = 0;
	for (size_t i = 0; i < str.size() - sub.size() + 1; ++i)
	{
		while ((j > 0) && (str[i] != sub[j]))
			j = pi[j - 1];

		if (str[i] == sub[j])
		++j;
		if (j == l)
		{
			delete[] pi;
			return i - l + 1;
		}
	}
	return std::string::npos;
}

std::vector<int> computeLPS(std::string pattern) {
	int n = pattern.length();
	std::vector<int> lps(n);

	int len = 0; // Length of the previous longest prefix suffix
	lps[0] = 0;

	int i = 1;
	while (i < n) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
			}
			else {
			if (len != 0) {
				len = lps[len-1];
				}
				else {
				lps[i] = 0;
				i++;
			}
		}
	}

	return lps;
}

int search(std::string text, std::string pattern) {
	int n = text.length();
	int m = pattern.length();

	int i = 0; // Pointer to text
	int j = 0; // Pointer to pattern

	std::vector<int> lps = computeLPS(pattern); // Compute LPS array

	while (i < n) {
		if (text[i] == pattern[j]) {
			i++;
			j++;
		}

		if (j == m) {
			// Found pattern at index i-j
			return i-j;
			}

			// Mismatch after j matches
			else if (i < n && text[i] != pattern[j]) {
			if (j != 0) {
				j = lps[j-1];
				}
				else {
				i++;
			}
		}
	}
	// Pattern not found
	return -1;
}




int main()
{
	Timer t;
	std::ifstream File("engwiki_ascii.txt");
	if (!File.is_open())
	{
		return 0;
	}
	const char* sub = "was born in a small town called Sceptre";
	std::string str;
	str.append((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());

	std::cout << "knuth-morris-pratt algorithm new" << std::endl;
	t.reset();
	std::cout << KMP::SubFind(sub, str.c_str()) << std::endl;
	t.timestamp();
	std::cout << t.elapsed_milliseconds() << " milliseconds" << std::endl;
	KMP::clear();

	std::cout << "boyer-moore algorithm" << std::endl;
	t.reset();
	std::cout << BM::SubFind(sub, str.c_str()) << std::endl;
	t.timestamp();
	std::cout << t.elapsed_milliseconds() << " milliseconds" << std::endl;

	std::cout << "std::find()" << std::endl;
	t.reset();
	std::cout << str.find(sub) << std::endl;
	t.timestamp();
	std::cout << t.elapsed_milliseconds() << " milliseconds" << std::endl;

	std::cout << "Naive search" << std::endl;
	t.reset();
	std::cout << naive(sub, str.c_str()) << std::endl;
	t.timestamp();
	std::cout << t.elapsed_milliseconds() << " milliseconds" << std::endl;

	return 0;
}
