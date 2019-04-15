#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <functional>

namespace qi = boost::spirit::qi;

struct foo {
  void do_action(const int& n) {
    std::cout << n << std::endl;
  }
  void parse(const std::string& input) {
    	qi::parse( input.begin(), input.end(), qi::int_[std::bind(&foo::do_action, this, std::placeholders::_1)] ); 
	}
};

int main() {
	std::string input = "123";
	foo f;
	f.parse( input );
	return 0;
}
