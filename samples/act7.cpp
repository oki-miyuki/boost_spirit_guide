#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

struct foo {
	int value_;

  void parse(const std::string& input) {
    qi::parse( input.begin(), input.end(), 
      qi::int_[ph::bind( &foo::value_, this ) = qi::_1 - 1] 	);
    std::cout << foo::value_ << std::endl;  
  }
};

int main() {
	std::string input = "2";
	foo f;
	f.parse(input);
	return 0;
}
