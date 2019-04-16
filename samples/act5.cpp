#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
//namespace ph = boost::phoenix;

int main() {
	std::string input = "2";
	int n;
	qi::parse( input.begin(), input.end(), qi::int_[qi::_val = qi::_1 * 2], n 	);
	std::cout << n << std::endl;
	return 0;
}
