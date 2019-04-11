#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345,abcd,54321";
	int n, m;
	std::string s;
	qi::parse( input.begin(), input.end(), qi::int_ >> ',' >> +(qi::standard::char_ - ',') >> ',' >> qi::int_, n, s, m ); 
	std::cout << n << "," << s << "," << m << std::endl;
	return 0;
}
