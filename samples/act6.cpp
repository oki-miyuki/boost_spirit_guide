#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

namespace foo {
	int value_;
}

int main() {
	std::string input = "2";
	qi::parse( input.begin(), input.end(), qi::int_[ph::ref(foo::value_) = qi::_1] 	);
	std::cout << foo::value_ << std::endl;
	return 0;
}
