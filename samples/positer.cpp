#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <iomanip>
#include <strstream>

#include "position_helper.hpp"
#include "cpp_comment_grammar.hpp"

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

struct NullActor {
  void rule1(int n) {}
  void rule2(short n) {}
  void rule3(const std::string& s) {}
};

template <typename Iterator, typename Skipper, typename Actor>
struct my_grammar : qi::grammar<Iterator, qi::unused_type(), Skipper>
{
  Actor* actor_;
  qi::rule<Iterator, int(), Skipper>  rule1_;
  qi::rule<Iterator, short(), Skipper>  rule2_;
  qi::rule<Iterator, std::string(), Skipper>  rule3_;
  qi::rule<Iterator, qi::unused_type(), Skipper>  start_;
  my_grammar(Actor* actor) 
    : my_grammar::base_type(start_, "my_grammar")
    , actor_(actor)
  {
    rule1_ = "rule1(" > qi::int_  > ')';
    rule2_ = "rule2(" > qi::short_ > ')';
    rule3_ = "rule3(" > +(qi::standard::char_ - ')') > ')';
    start_ = +(
        rule1_[std::bind( &Actor::rule1, actor_, std::placeholders::_1)]
      | rule2_[std::bind( &Actor::rule2, actor_, std::placeholders::_1)]
      | rule3_[std::bind( &Actor::rule3, actor_, std::placeholders::_1)]
    );
  }  
};

namespace {
  // position_iterator から構文解析に失敗した位置情報を出力する
  std::string toErrorMsg(const pos_iterator_type& iter, const char* fn) {
    const boost::spirit::classic::file_position_base<std::string>& pos = iter.get_position();
    std::ostringstream msg;
    msg <<
      "parse error at file :" << fn <<
      " line " << pos.line << " column " << pos.column << "\r\n" <<
      "'" << iter.get_currentline() << "'" << "\r\n" <<
      std::setw(pos.column) << " " << "^- here\r\n";
    return msg.str();
  }
}

int main(int argc, char* argv[]) {
  if( argc != 2 ) {
    std::cout << "positer filename" << std::endl;
    return 0;
  }
  std::ifstream ifs;
  ifs.open(argv[1]);
  if( !ifs.good() ) { 
    std::cerr << "fail to read :" << argv[1] << std::endl;
    return 1;
  }

  BOOST_SPIRIT_POS_ITERATOR(ifs)
  
  NullActor act;

  my_grammar<
    pos_iterator_type,
    cpp_comment_grammar<pos_iterator_type>,
    NullActor
  >  my_rule(&act);
  cpp_comment_grammar<pos_iterator_type>  skipper;
  pos_iterator_type iter = position_begin;
  bool result = false;
  try {
    result = qi::phrase_parse(iter, position_end, my_rule, skipper);
    if (iter == position_end) {
      std::cout << "success\r\n";
    }
    else {
      std::cerr << toErrorMsg(iter, argv[1]);
      return 1;
    }
  } catch(const qi::expectation_failure<pos_iterator_type>& e) {
    std::cerr << toErrorMsg(e.first, argv[1]);
    return 1;
  }
  return 0;
}
