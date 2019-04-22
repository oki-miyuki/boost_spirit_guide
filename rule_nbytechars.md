# Nバイト文字の処理

  文字コードは Shift JIS, EUC JP, UTF-8, UNICODE 等、色々あります。
  UTF-8 と UNICODE の処理は、ほぼ同じで、qi::standard::char_ を使用するか、qi::standard_wide::char_ を使用するか程度の違いしかありません。
  コードセットと文字名前空間の対応は下記です。  

| コードセット | 別名 | 文字名前空間 |
|:--|:--|:--|
| 932 | CP932, Shift JIS | qi::standard::char_ |
| 20932 | EUC-JP | qi::standard::char_ |
| 50932 | EUC-JP | qi::standard::char_ |
| 65001 | UTF-8 | qi::standard::char_ |


## Shift JIS の取扱い

単純にコードの並びをルール化してやればOKです。
```
  // SJIS 第1バイト候補
  qi::rule<Iterator, char(), Skipper> sjis1_t = (qi::char_(0x81,0x9f) | qi::char_(0xe0,0xfc));
  // SJIS 第2バイト候補
  qi::rule<Iterator, char(), Skipper> sjis2_t = (qi::char_(0x40,0x7e) | qi::char_(0x80,0xfc));
  // 漢字のみルール
  qi::rule<Iterator, std::string(), Skipper> kanji_t = *(sjis1_t > sjis2_t);
```

  SJIS漢字処理サンプル
```
C++: SJIS漢字処理
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

std::vector<std::string> strvec;

template <typename Iterator, typename Skipper>
struct kanji_grammar : qi::grammar<Iterator, qi::unused_type(), Skipper>
{
public:
	kanji_grammar() : kanji_grammar::base_type(start) {
		sjis1_t = (qi::char_(0x81,0x9f) | qi::char_(0xe0,0xfc));
		sjis2_t = (qi::char_(0x40,0x7e) | qi::char_(0x80,0xfc));
		kname_t = + (sjis1_t > sjis2_t);
		start = *(kname_t[ph::push_back(ph::ref(strvec), qi::_1)] % ',');
	}
	qi::rule<Iterator, char(), Skipper> sjis1_t;
	qi::rule<Iterator, char(), Skipper> sjis2_t;
	qi::rule<Iterator, std::string(), Skipper> kname_t;
	qi::rule<Iterator, qi::unused_type(), Skipper> start;
};

int main() {
	std::string input = "ハロー,漢字,処理";
	kanji_grammar<std::string::iterator,qi::standard::space_type> grammar;
	qi::phrase_parse(input.begin(), input.end(), grammar, qi::standard::space);
	for( std::string str : strvec ) {
		std::cout << "¥'" << str << "¥'¥n";
	}
	return 0;
}
```  
