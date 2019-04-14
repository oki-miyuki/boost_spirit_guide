#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "04142019";
	int year, month, day;
	qi::parse( input.begin(), input.end(), 
	     qi::raw[qi::repeat(2)[qi::standard::digit]] 
	     >> qi::raw[qi::repeat(2)[qi::standard::digit]] 
	     >> qi::raw[qi::repeat(4)[qi::standard::digit]] 
	  , month, day, year ); 
	std::cout << year << "/" << month << "/" << day << std::endl;
	return 0;
}
