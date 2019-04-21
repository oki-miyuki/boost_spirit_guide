#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, std::string(), Skipper>
{
  qi::rule<Iterator, std::string(), Skipper>  start_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = +qi::char_;
  }
};

int main() {
  std::string input = "abc 12345";
  std::string n;
  my_grammar<std::string::iterator,qi::standard::space_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, qi::standard::space, n );
  std::cout << n << std::endl;
  return 0;
}
