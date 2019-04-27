#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;


template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, std::vector<std::pair<int,int>>(), Skipper> {
  qi::rule<Iterator, std::vector<std::pair<int,int>>(), Skipper>  start_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = *( '{' >> qi::int_ >> ',' >> qi::int_ >> '}' );
  }
};

int main() {
  std::string input = "{ 1, 10 } { 100, 1000 } ";
  std::vector<std::pair<int,int>> v;
  my_grammar<std::string::iterator, qi::standard::space_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, qi::standard::space, v );
  for( std::pair<int,int> p : v ) {
	  std::cout << p.first << " - " << p.second << std::endl;
  }
  return 0;
}
