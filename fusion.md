# 構造体を読む(fusion)

  boost/fusion/adapted/struct/adapt_struct.hpp というヘッダーに  
  構造体を読むための BOOST\_FUSION\_ADAPT\_STRUCT というマクロが用意されています。  

```
  BOOST_FUSION_ADAPT_STRUCT(  
    構造体名  
    (メンバ変数の型, メンバ変数名)  
    ... 繰り返し  
  )  
```

構造体を読む例
```
C++: 構造体を読む例
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;

struct foo {
  int index_;
  std::string name_;
  bool flag1_;
  bool flag2_;
  long val_;
};

BOOST_FUSION_ADAPT_STRUCT(
  foo,
  (int,         index_)
  (std::string, name_)
  (bool,        flag1_)
  (bool,        flag2_)
  (long,        val_)
)

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, std::vector<foo>(), Skipper> {
  qi::rule<Iterator, std::vector<foo>(), Skipper>  start_;
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = *(
      '{' 
        >> qi::int_ >> ',' 
        >> +qi::standard::alnum >> ','
        >> qi::bool_ >> ','
        >> qi::bool_ >> ','
        >> qi::long_ >>
      '}'
    );
  }
};

int main() {
  std::string input = "{ 1, taro, true, false, 25 } { 2, hanako, false, true, 22 } ";
  std::vector<foo> v;
  my_grammar<std::string::iterator, qi::standard::space_type> myg;
  qi::phrase_parse( input.begin(), input.end(), myg, qi::standard::space, v );
  for( foo f : v ) {
    std::cout << "--------------" << std::endl;
    std::cout << f.index_ << std::endl;
    std::cout << f.name_ << std::endl;
    std::cout << f.flag1_ << std::endl;
    std::cout << f.flag2_ << std::endl;
    std::cout << f.val_ << std::endl;
  }
  return 0;
}
```
