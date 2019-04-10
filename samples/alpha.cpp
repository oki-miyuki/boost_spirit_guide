#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

void do_alpha(const char val) {
	std::cout << val << " ";
}

int main() {
	std::string input = "abcdefAZ¥r¥nほげ";
	qi::parse( input.begin(), input.end(), *(qi::standard::alpha[phx::bind(do_alpha, qi::_1)] | qi::standard::char_) );
	std::cout << std::endl;
	return 0;
}
