#include "Boxplot.hpp"

double BoxPlot::median(std::vector<double> vec)
{
	long int n = vec.size();
	if (n % 2 == 1) 
	{
		std::nth_element(vec.begin(), vec.begin() + n / 2, vec.end());
		return vec[n / 2];
	}
	else 
	{
		std::nth_element(vec.begin(), vec.begin() + n / 2, vec.end());
		double a = vec[n / 2];
		std::nth_element(vec.begin(), vec.begin() + n / 2 - 1, vec.end());
		double b = vec[n / 2 - 1];
		return (a + b) / 2.0;
	}
}

double BoxPlot::lq(std::vector<double> vec)
{
	long int n = vec.size();
	if (n % 2 == 1)
	{
		std::nth_element(vec.begin(), vec.begin() + n / 4, vec.end());
		return vec[n / 4];
	}
	else
	{
		std::nth_element(vec.begin(), vec.begin() + n / 4, vec.end());
		double a = vec[n / 4];
		std::nth_element(vec.begin(), vec.begin() + n / 4 - 1, vec.end());
		double b = vec[n / 4 - 1];
		return (a + b) / 2.0;
	}
}

double BoxPlot::uq(std::vector<double> vec)
{
	long int n = vec.size();
	if (n % 2 == 1)
	{
		std::nth_element(vec.begin(), vec.begin() + 3 * n / 4, vec.end());
		return vec[3 * n / 4];
	}
	else
	{
		std::nth_element(vec.begin(), vec.begin() + 3 * n / 4, vec.end());
		double a = vec[3 * n / 4];
		std::nth_element(vec.begin(), vec.begin() + 3 * n / 4 - 1, vec.end());
		double b = vec[3 * n / 4 - 1];
		return (a + b) / 2.0;
	}
}

double BoxPlot::min(std::vector<double> &vec)
{
	return lq(vec) - 1.5 * (uq(vec) - lq(vec));
}

double BoxPlot::max(std::vector<double> &vec)
{
	return uq(vec) + 1.5 * (uq(vec) - lq(vec));
}

double BoxPlot::mean(std::vector<double> &vec)
{
	return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double BoxPlot::stddev(std::vector<double> &vec)
{
	double mo = mean(vec);
	double disp = .0;
	for (double it : vec) disp += pow((it - mo), 2);
	return sqrt(disp / (vec.size() - 1));
}

std::vector<double> BoxPlot::out(std::vector<double> &vec)
{
	double mx = max(vec);
	double mn = min(vec);
	std::vector<double> ans;
	for (auto it : vec) if (it > mx || it < mn) ans.push_back(it);
	return ans;
}
