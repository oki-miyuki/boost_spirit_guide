#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

void do_action() {
	std::cout << "do_action()" << std::endl;
}

int main() {
	std::string input = "action";
	qi::parse( input.begin(), input.end(), qi::lit("action")[do_action] );
	return 0;
}