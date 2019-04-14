#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

void do_action1() { std::cout << "hello"; }
void do_action2() { std::cout << " action" << std::endl; }

int main() {
	std::string input = " ";
	qi::parse( input.begin(), input.end(), 
	     qi::eps[do_action1] >> ' ' >> qi::eps[do_action2]
	);
	return 0;
}
