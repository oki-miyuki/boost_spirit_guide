#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

void do_action(const int& n, qi::unused_type ctx, bool& abort) {
  if( n > 2 ) {
    abort = false; // ルールをマッチさせない
    return;
  }
  std::cout << n << std::endl;
}

int main() {
	std::string input = "0 1 2 3 4";
	qi::parse( input.begin(), input.end(), *(qi::int_[do_action] % ' ')	);
	return 0;
}
