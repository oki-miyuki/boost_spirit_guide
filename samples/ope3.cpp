#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "dog(2pochi),cat(tama)";
	std::vector<std::string> v;
	qi::parse( input.begin(), input.end(), 
	  *( 
	    (
	     //("dog(" >> +qi::standard::char_("a-z")  >> ')')
	     ("dog(" > +qi::standard::char_("a-z")  > ')')
	     | (+qi::omit[qi::standard::alpha] > '(' > +qi::standard::alnum > ')')
	    ) % ','
	  )
	  , v ); 
	for(std::string n: v) { std::cout << n << std::endl; }
	return 0;
}
