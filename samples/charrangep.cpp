#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "FBIJHCBFIJXXX";
	std::string n;
	qi::parse( input.begin(), input.end(), +qi::standard::char_('A', 'J'), n );
	std::cout << n << std::endl; // Xはルールにマッチしないので FBIJHCBFIJ まで表示されます
	return 0;
}
