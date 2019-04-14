#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <vector>

namespace qi = boost::spirit::qi;

void do_action(const std::vector<int>& v) { for(int n: v ) { std::cout << n << std::endl; } }

int main() {
	std::string input = "1 2";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), 
	  qi::as<std::vector<int>>()[qi::int_ >> ' ' >> qi::int_][do_action],
	  v
	);
	return 0;
}
