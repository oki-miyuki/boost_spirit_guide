#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, unsigned(), Skipper> {
  qi::rule<Iterator, unsigned(), Skipper>  start_;
  qi::uint_parser<unsigned,10,0,255>       sample_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = ( 
      "rgb(" > sample_ > ',' > sample_ > ',' > sample_ > ')'
      )[qi::_val = ((qi::_1 << 16) + (qi::_2 << 8) + qi::_3)];
  }
};

int main() {
  std::string input = "rgb(255,172,120)";
  unsigned rgb;
  my_grammar<std::string::iterator, qi::standard::space_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, qi::standard::space, rgb );
  std::cout << std::hex << rgb << std::endl;
  return 0;
}
