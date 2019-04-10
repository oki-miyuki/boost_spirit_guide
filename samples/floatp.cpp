#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "3.14159";
	float n;
	qi::parse( input.begin(), input.end(), qi::float_, n );
	std::cout << n << std::endl;
	return 0;
}
