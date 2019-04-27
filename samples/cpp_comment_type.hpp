#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct cpp_comment_grammar : qi::grammar<Iterator> {
public:
  cpp_comment_grammar() : cpp_comment_grammar::base_type(start) {
    start = qi::standard::blank | comment_nest_p | comment_p;
    comment_nest_p = qi::lit("/*") > *(qi::standard::char_ - qi::lit("*/") - qi::eoi) > qi::lit("*/");
    comment_p = qi::lit("//") > *(qi::standard::char_ - qi::eol -qi::eoi) > (qi::eol | qi::eoi);
  }
  qi::rule<Iterator> start;
  qi::rule<Iterator> comment_nest_p;
  qi::rule<Iterator> comment_p;
};
