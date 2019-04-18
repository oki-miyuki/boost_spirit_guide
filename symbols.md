# Symbols

  文字列の組み合わせを好きな型の値と連想させる事ができます。  
  namespace qi = boost::spirit::qi;

定義は以下
```
template <typename Char, typename T, typename Lookup>
struct symbols;
```
  Char = char型  
  T = 属性(値型)  
  Lookup = 文字列サーチクラス(デフォルトは tst_map<char,T>)  
  ただし、T は Primitive Type の要件を満たす必要があります。  

```
C++: char enum
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

enum class Color { red, green, blue };

std::ostream& operator << (std::ostream& os, Color c) {
	if( c == Color::red ) os << "red";
	else if( c == Color::green ) os << "green";
	else if( c == Color::blue )  os << "blue";
	else os << "unknown";
	return os;
}

qi::symbols<char,Color>  color_;

int main() {

  // runtime 時に追加します。解析結果を追加する事もできるという事
  color_.add
    ("red", Color::red)
    ("green", Color::green)
    ("blue", Color::blue)
  ;

	std::string input = "green";
	Color c;
	qi::parse( input.begin(), input.end(), color_, c );
	std::cout << c << std::endl;
	return 0;
}
```
