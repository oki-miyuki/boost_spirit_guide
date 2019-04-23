#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct c_comment_grammar : qi::grammar<Iterator> {
public:
  c_comment_grammar() : c_comment_grammar::base_type(start) {
    start = qi::standard::blank | comment_nest_p | comment_p;
    comment_nest_p = qi::lit("/*") > *(qi::standard::char_ - qi::lit("*/") - qi::eoi) > qi::lit("*/");
    comment_p = qi::lit("//") > *(qi::standard::char_ - qi::eol -qi::eoi) > (qi::eol | qi::eoi);
  }
  qi::rule<Iterator> start;
  qi::rule<Iterator> comment_nest_p;
  qi::rule<Iterator> comment_p;
};

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, int(), Skipper> {
  qi::rule<Iterator, int(), Skipper>  start_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = qi::int_;
  }
};

int main() {
  std::string input = "// これはコメントです。\n /* これもコメント */ 12345";
  int n;
  typedef c_comment_grammar<std::string::iterator> c_comment_type;
  c_comment_type comment;
  my_grammar<std::string::iterator, c_comment_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, comment, n );
  std::cout << n << std::endl;
  return 0;
}
