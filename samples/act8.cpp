#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <vector>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

struct foo {
	std::vector<int> value_;

  void parse(const std::string& input) {
    qi::parse( input.begin(), input.end(), 
      *(qi::int_[ph::push_back(ph::bind( &foo::value_, this ), qi::_1 - 1)] % ',') );
    for( int n: value_) {
      std::cout << n << ","; 
    } 
    std::cout << std::endl;
  }
};

int main() {
	std::string input = "2,4,6,8";
	foo f;
	f.parse(input);
	return 0;
}
