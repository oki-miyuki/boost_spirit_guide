#include <boost/spirit/include/qi.hpp>

template <typename Iterator>
struct cpp_comment_grammar : boost::spirit::qi::grammar<Iterator> {
public:
  cpp_comment_grammar() : cpp_comment_grammar::base_type(start) {
    namespace qi = boost::spirit::qi;
    start = qi::standard::space | comment_nest_p | comment_p;
    comment_nest_p = qi::lit("/*") > *(qi::standard::char_ - qi::lit("*/") - qi::eoi) > qi::lit("*/");
    comment_p = qi::lit("//") > *(qi::standard::char_ - qi::eol -qi::eoi) > (qi::eol | qi::eoi);
  }
  boost::spirit::qi::rule<Iterator> start;
  boost::spirit::qi::rule<Iterator> comment_nest_p;
  boost::spirit::qi::rule<Iterator> comment_p;
};

