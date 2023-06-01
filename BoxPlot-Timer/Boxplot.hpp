#pragma once
#include <math.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

class BoxPlot
{
public:
	static double min(std::vector<double> &vec);
	static double lq(std::vector<double> vec);
	static double median(std::vector<double> vec);
	static double mean(std::vector<double> &vec);
	static double stddev(std::vector<double> &vec);
	static double uq(std::vector<double> vec);
	static double max(std::vector<double> &vec);
	static std::vector<double> out(std::vector<double> &vec);
	
};
