#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "こんにちは"; // Windows では SJIS解釈、他では UTF-8解釈
	auto s = input.begin();
	auto e = input.end();
	qi::parse( s, e, qi::lit("こんにちは") );
	//qi::parse( s, e, qi::lit("こんにちわ") );
	std::cout << ((s == e) ? "マッチ" : "エラー") << std::endl;
	return 0;
}
