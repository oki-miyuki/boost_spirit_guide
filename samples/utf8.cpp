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