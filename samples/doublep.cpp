#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <iomanip>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "8e-5";
	double n;
	qi::parse( input.begin(), input.end(), qi::double_, n );
	std::cout << std::fixed << n << std::endl;
	return 0;
}
