#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "こんにちは"; // Windows では SJIS解釈、他では UTF-8解釈
	std::string n;
	qi::parse( input.begin(), input.end(), qi::lit("こんにちわ"), n );
	std::cout << n << std::endl;
	return 0;
}
