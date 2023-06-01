#include <iostream>
#include <vector>
#include "Timer.hpp"
#include "Boxplot.hpp"

using namespace std;

long fibonacci(unsigned n) {
	return n < 2 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{

	Timer t;
	std::cout << "f(42) = " << fibonacci(8) << '\n';
	t.timestamp();
	std::cout << t.elapsed_minutes() << std::endl;
	std::cout << t.elapsed_seconds() << std::endl;
	std::cout << t.elapsed_milliseconds() << std::endl;
	std::cout  << std::endl;
	std::vector<double> x = { 0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
	std::cout.precision(2);
	std::cout << std::scientific << "min:\t" << BoxPlot::min(x) << std::endl;
	std::cout << std::scientific << "lq:\t" << BoxPlot::lq(x) << std::endl;
	std::cout << std::scientific << "median:\t" << BoxPlot::median(x) << std::endl;
	std::cout << std::scientific << "mean:\t" << BoxPlot::mean(x) << std::endl;
	std::cout << std::scientific << "stddev:\t" << BoxPlot::stddev(x) << std::endl;
	std::cout << std::scientific << "uq:\t" << BoxPlot::uq(x) << std::endl;
	std::cout << std::scientific << "max:\t" << BoxPlot::max(x) << std::endl;
	auto outs = BoxPlot::out(x);
	std::cout << "out:\t";
		for (const auto & it : outs)
			std::cout << std::scientific << it << std::endl;
	std::cout << std::endl;

	return 0;
}
