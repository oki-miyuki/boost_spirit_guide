#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "true false";
	bool a, b;
	qi::parse( input.begin(), input.end(), qi::bool_ >> ' ' >> qi::bool_, a, b );
	std::cout << a << "," << b << std::endl;
	return 0;
}
