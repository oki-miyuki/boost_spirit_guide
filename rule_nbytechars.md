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
C++: SJIS漢字処理(Windows)
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

## EUC-JP

SJIS同様に以下のように定義していけば処理できるでしょう。
```
  // EUC-JP かな系第1バイト候補
  qi::rule<Iterator, char(), Skipper> eucjpkana1_t = qi::char_(0xa1,0xa8);
  // EUC-JP jisx208第1バイト候補
  qi::rule<Iterator, char(), Skipper> eucjp1_t = qi::char_(0xb0,0xf4);
  // EUC-JP 第2バイト候補
  qi::rule<Iterator, char(), Skipper> eucjp2_t = qi::char_(0xa1,0xFE);
  // 漢字のみルール
  qi::rule<Iterator, std::string(), Skipper> kanji_t = *(eucjp1_t > eucjp2_t);
```

## UTF-8

以下のようなコード体系になります。
```
  // ASCII 範囲
  qi::rule<Iterator, char(), Skipper> utf81_t = qi::char_(0x00,0x7f);
  // 2バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf82_t = qi::char_(0xc2,0xdf);
  // 3バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf83_t = qi::char_(0xe0,0xef);
  // 4バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf84_t = qi::char_(0xf0,0xf7);
  // 2バイト以上表現の第2バイト以降候補
  qi::rule<Iterator, char(), Skipper> utf8n_t = qi::char_(0x80,0xbf);
  // ASCII 以外の範囲
  qi::rule<Iterator, std::string(), Skipper> kanji_t 
    = *( 
        (utf82_t > utf8n_t)
      | (utf83_t > utf8n_t > utf8n_t)
      | (utf84_t > utf8n_t > utf8n_t > utf8n_t)
    );
```

UTF8 漢字処理サンプル
```
C++: UtF-8 漢字処理(Linux,Mac)
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
    utf81_t = qi::char_(0x00,0x7f);
    utf82_t = qi::char_(0xc2,0xdf);
    utf83_t = qi::char_(0xe0,0xef);
    utf84_t = qi::char_(0xf0,0xf7);
    utf8n_t = qi::char_(0x80,0xbf);
    kname_t 
      = +( 
          (utf84_t > utf8n_t > utf8n_t > utf8n_t)
        | (utf83_t > utf8n_t > utf8n_t)
        | (utf82_t > utf8n_t)
      );
		start = *(kname_t[ph::push_back(ph::ref(strvec), qi::_1)] % ',');
	}
  qi::rule<Iterator, char(), Skipper> utf81_t; // ASCII 範囲
  qi::rule<Iterator, char(), Skipper> utf82_t; // 2バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf83_t; // 3バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf84_t; // 4バイト表現コードの第1バイト候補
  qi::rule<Iterator, char(), Skipper> utf8n_t; // 2バイト以上表現の第2バイト以降候補
  qi::rule<Iterator, std::string(), Skipper> kname_t;  // ASCII 以外の範囲
	qi::rule<Iterator, qi::unused_type(), Skipper> start;
};

int main() {
	std::string input = "ハロー,漢字,処理";
	kanji_grammar<std::string::iterator,qi::standard::space_type> grammar;
	qi::phrase_parse(input.begin(), input.end(), grammar, qi::standard::space);
	for( std::string str : strvec ) {
		std::cout << "\'" << str << "\'\n";
	}
	return 0;
}
```
