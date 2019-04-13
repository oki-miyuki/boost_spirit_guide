#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

int main() {
	std::string input = "abcde";
	std::string str;
	qi::parse( input.begin(), input.end(), qi::lazy(ph::val(qi::string("abcde"))), str );
	std::cout << str << std::endl;
	return 0;
}
