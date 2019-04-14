#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

int main() {
	std::string input = "one two three";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), 
	  *(
	    (
    	   (qi::lit("one") >> qi::attr(1)) 
	    | (qi::lit("two") >> qi::attr(2)) 
	    | (qi::lit("three") >> qi::attr(3))
	    ) % qi::standard::blank
	   ), 
	   v 
	 );
	for( int n : v ) { std::cout << n << std::endl; }
	return 0;
}
