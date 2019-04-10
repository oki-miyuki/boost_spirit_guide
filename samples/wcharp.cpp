#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::wstring input = L"日";
	wchar_t n;
	qi::parse( input.begin(), input.end(), qi::standard_wide::char_, n );
	std::wcout.imbue(std::locale(""));
	std::wcout << n << std::endl;
	return 0;
}
