#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345 223  54321";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), *( qi::int_ % +qi::standard::blank), v ); 
	for(int n: v) { std::cout << n << std::endl; }
	return 0;
}
