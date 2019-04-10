#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "256";
	unsigned short n;
	qi::parse( input.begin(), input.end(), qi::ushort_, n );
	std::cout << n << std::endl;
	return 0;
}
