#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

enum class Color { red, green, blue };

std::ostream& operator << (std::ostream& os, Color c) {
	if( c == Color::red ) os << "red";
	else if( c == Color::green ) os << "green";
	else if( c == Color::blue )  os << "blue";
	else os << "unknown";
	return os;
}

qi::symbols<char,Color>  color_;

int main() {

  color_.add
    ("red", Color::red)
    ("green", Color::green)
    ("blue", Color::blue)
  ;

	std::string input = "green";
	Color c;
	qi::parse( input.begin(), input.end(), color_, c );
	std::cout << c << std::endl;
	return 0;
}
