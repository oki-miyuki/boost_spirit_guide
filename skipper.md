# コメント構文(Skipper)

  spirit の設計には、コメントを透過的に処理できる機構が組み込まれています。  
  Skipper というものがそれで、パーサ・ディレクティブにも skip, no_skip といったものがあります。  
  通常の構文に対して、コメントとなる構文を柔軟に指定できるようになっています。  
  
  組込のSkipperとして、文字分類パーサが用意されています。  
  ns は、qi::standard, qi::standard\_wide, qi::ascii, qi::iso8859\_1 の何れかです。  
  
| 文字分類 | ルール | コメント構文型 |
|:--|:--|:--|
|ブランク|ns::blank|ns::blank_type|
|スペース|ns::space|ns::space_type|　

## 独自のコメント

  通常の構文をコメント構文として利用できます。
  Skipper に対する Skipper は無いので、template paramater の Skipper は省略します。  
  省略された場合は、qi::unused_type が適用されます。  
  コメントの属性は使用しないので、同様に qi::unused_type() で省略します。  

C++ スタイルのコメント
```
C++: C++スタイルコメント
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
```

以下、独自のコメントを流用してみます。
```
C++: C++スタイルコメント利用例
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
```