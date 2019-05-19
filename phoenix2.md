# フェニックスとプレースホルダ

  [セマンティック・アクション](semantic_action.md) でphoenixのプレースホルダ qi::\_2, qi::\_3 の説明を飛ばしたので、ここで解説します。   
  boost::phoenix のプレースホルダは、qi::\_val, qi::\_1, qi::\_2, qi::\_3 になります。  
  qi::\_val がインスタンスになり、ルール中の基本パーサに対応する値が qi::\_1, qi::\_2, qi::\_3, ... になります。  
  ルールでインスタンスに対して、プレースホルダを利用して値を計算させる事ができます。  
 
RGB値を読み込むサンプル 
```
C++: qi::_2, qi::_3を使った例
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, unsigned(), Skipper> {
  qi::rule<Iterator, unsigned(), Skipper>  start_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = ( 
      '#' >> qi::uint_parser<unsigned,16,2,2>() 
          >> qi::uint_parser<unsigned,16,2,2>()
          >> qi::uint_parser<unsigned,16,2,2>()
      )[qi::_val = qi::_1 << 16 + qi::_2 << 8 + qi::_3];
  }
};

int main() {
  std::string input = "#FF0000";
  unsigned rgb;
  my_grammar<std::string::iterator, qi::standard::space_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, qi::standard::space, rgb );
  std::cout << std::hex << rgb << std::endl;
  return 0;
}
```