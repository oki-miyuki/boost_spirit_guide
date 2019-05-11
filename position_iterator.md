# エラー箇所の表示(PositionIterator)

  構文解析にエラーは付き物です。業務用のコードを書くにあたって、どこでエラーが起こったかわからないようなものは、業務用として使用に耐えません。  
  何行目の何文字目で構文エラーになったという報告をするためのクラスが用意されています。  
  boost/spirit/include/classic_position_iterator.hpp  
  ファイルのエラー位置を記録するIteratorクラスが宣言されています。  
  boost/spirit/include/support_multi_pass.hpp  
  stream系クラスには、位置を保持する機構がありません。Iterator を複数保持する事により擬似ランダムアクセスを実現するのが multi_pass です。  

  この機構を利用しなくても、qi::parse または qi::phrase_parse に失敗した場合
  Iterator::begin を渡した位置が解析に失敗した位置になるため、この位置までの改行コード数を数えることで同じ機能を実現する事は可能です。  
  
  利用するには、以下の定義を用意しておいて利用します。
```
C++:position_iterator.hpp
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
/**
 * ファイルのエラー箇所を報告できるようにするための
 * postion_iterator の型定義
 */
typedef std::istreambuf_iterator<char> base_iterator_type;
typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
typedef boost::spirit::classic::position_iterator2<forward_iterator_type> pos_iterator_type;

/// stream に対して、ファイルエラー箇所を報告できるようにするためのマクロ
#define BOOST_SPIRIT_POS_ITERATOR( input_stream ) \
  base_iterator_type in_begin(input_stream); \
  base_iterator_type in_end; \
  forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin); \
  forward_iterator_type fwd_end = boost::spirit::make_default_multi_pass(in_end); \
  pos_iterator_type position_begin(fwd_begin, fwd_end, ""); \
  pos_iterator_type position_end; 
```

エラー箇所表示サンプル
```
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <iomanip>
#include <strstream>

// 本頁の解説より拝借
#include "position_helper.hpp"
// コメント構文(Skipper) より拝借
#include "cpp_comment_grammar.hpp"

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

// 何もしない Actor
struct NullActor {
  void rule1(int n) {}
  void rule2(short n) {}
  void rule3(const std::string& s) {}
};

// Actor を交換できるようにテンプレート・パラメータに追加
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
```

サンプルに引き渡すtxt例
```
 rule1(1)
 rule3(hello)
 rule2(-1)
 rule1(hiho)
 //rule4(hoge)
 rule1(3)
```