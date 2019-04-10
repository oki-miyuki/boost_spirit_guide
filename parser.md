# パーサ
## 基本
  まずは、文字列の入力から値を取り出すための基本ルールを見て行きましょう。基本ルールの確認は、下記のようなコードで行います。
ルールにマッチしない入力は、解析に失敗します。
```
c++:基本のコード
#include <boost/spirit/include/qi.hpp>  // boost::spirit::qi を利用します
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;  // namespaceが長いので qi にします

int main() {
	std::string input = "12345"; // 解析させる入力です。値を書き換えて遊んでください
	int n;  // 解析された結果を格納するための変数です。この部分は記述するルールに応じて変わります。
	qi::parse( // 解析をする関数本体です
	  input.begin(), input.end(), // 解析させる入力の指定 
	  qi::int_, // 解析するルール
	  n // 解析された結果を格納するための変数
	); 
	std::cout << n << std::endl; // 解析された結果を確認します。
	return 0;
}
```

## 数値パーサ
  数値型に応じた組み込み型のパーサが用意されています。(namespace qi = boost::spirit::qi)
  
| 数値型 | ルール |
|:--|:--|
|short|qi::short_|
|unsigned short|qi::ushort_|
|int|qi::int_|
|unsigned int|qi::uint_|
|long|qi::long_|
|unsigned long|qi::ulong_|
|long long|qi::long_long|
|unsigned long long|qi::ulong_long|
|float|qi::float_|
|double|qi::double_|
|long double|qi::long_double|

```
c++:double 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <iomanip>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "8e5";
	double n;
	qi::parse( input.begin(), input.end(), qi::double_, n );
	std::cout << std::fixed << n << std::endl;
	return 0;
}
```

```
c++:float 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "3.14125";
	float n;
	qi::parse( input.begin(), input.end(), qi::float_, n );
	std::cout << n << std::endl;
	return 0;
}
```

```
c++:unsigned short 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "256";
	unsigned short n;
	qi::parse( input.begin(), input.end(), qi::ushort_, n );
	std::cout << n << std::endl;
	return 0;
}
```

## 文字パーサ
  ルールは char_ になりますが、想定する文字コードに応じて名前空間が異なります。(namespace qi = boost::spirit::qi)
 * qi::ascii
 * qi::iso8859_1
 * qi::standard
 * qi::standard_wide
 
 この辺の設計は流動的ですので、standard, standard_wide の２つを押さえておけば問題ありません。
 ascii 及び [iso8859_1](https://ja.wikipedia.org/wiki/ISO/IEC_8859-1) は、standard に含まれます。shift_jis, euc_jp という名前空間は存在しませんが、standard に含まれます。
 
| 文字型 | ルール |
|:--|:--|
|char|qi::standard::char_|
|wchar_t|qi::standard_wide::char_|
|'X'|
|"文字列定数"|qi::lit("文字列定数")|
|L"文字列定数"|qi::lit(L"文字列定数")|
|std::string|+(qi::standard::char_)|
|std::wstring|+(qi::standard_wide::char_)|

ここでルールに + という記号が登場しました。ルールに適応できる演算子で、1回以上の繰り返しを示します。似た演算子で * という0回以上の繰り返しを示すものもあります。
正規表現では同じ意味を持つ + * は後置演算子ですが、C++ の文法で実現するために前置演算子として実装されています。char型の繰り返しをstring型として取り出せるところが巧妙です。
  
```
c++:char 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "a";
	char n;
	qi::parse( input.begin(), input.end(), qi::standard::char_, n );
	std::cout << n << std::endl;
	return 0;
}
```
 
```
c++:wchar 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::wstring input = L"日";
	wchar_t n;
	qi::parse( input.begin(), input.end(), qi::standard_wide::char_, n );
	std::wcout.imbue(std::locale(""));
	std::wcout << n << std::endl;
	return 0;
}
```

```
c++:文字列定数 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "こんにちは"; // Windows では SJIS解釈、他では UTF-8解釈
	std::string n;
	qi::parse( input.begin(), input.end(), qi::lit("こんにちは"), n );
	// こちらだと入力とマッチしないので解析に失敗し何も出力されない
	//qi::parse( input.begin(), input.end(), qi::lit("こんにちわ"), n );
	std::cout << n << std::endl;
	return 0;
}
```
  
```
c++:文字列定数 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::wstring input = L"こんにちは";
	std::wstring n;
	qi::parse( input.begin(), input.end(), qi::lit(L"こんにちは"), n );
	std::wcout.imbue(std::locale(""));
	std::wcout << n << std::endl;
	return 0;
}
```

### 応用
  qi::standard::char_, qi::standard_wide::char_ に対してマッチする文字を指定する事が可能です。
 ２通りの指定方法があります

 * 開始から終了までの範囲指定

| 引数 | 説明 | 例 |
|:--|:--|:--|
| qi::standard::char_( char arg1, char arg2 ) | arg1: 開始文字, arg2: 終了文字, 開始文字から終了文字までの文字にマッチする | qi::standard::char_('A','Z'); |
| qi::standard_wide::char_( wchar_t arg1, wchar_t arg2 ) | arg1: 開始文字, arg2: 終了文字, 開始文字から終了文字までの文字にマッチする | qi::standard_wide::char_(L'A', L'Z'); |

```
c++:範囲指定 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::wstring input = L"ABFHIJ";
	std::wstring n;
	qi::parse( input.begin(), input.end(), qi::char(L"こんにちは"), n );
	std::wcout.imbue(std::locale(""));
	std::wcout << n << std::endl;
	return 0;
}
```

| 引数 | 説明 | 例 |
|:--|:--|:--|
| qi::standard::char_( const char* arg ) | arg: 文字指定 | qi::standard::char_("A-Z"); |
| qi::standard_wide::char_( const wchar_t* arg ) | arg: 文字指定 | qi::standard:_wide::char_(L"a-fA-F0-9"); |

文字指定には

## 文字分類パーサ

  アルファベット、数字、空白文字、改行文字、というように、分類された文字のルールです。
文字パーサ同様、想定する文字コードに応じて名前空間が異なります。(namespace qi = boost::spirit::qi)

 * qi::ascii
 * qi::iso8859_1
 * qi::standard
 * qi::standard_wide
 
名前空間 ns は、以下の何れかに該当します
 
 * namespace ns = qi::ascii;
 * namespace ns = qi::iso8859_1;
 * namespace ns = qi::standard;
 * namespace ns = qi::standard_wide;

| 文字分類 | ルール | 例 |
|:--|:--|:--|
|アルファベット|ns::alpha|a-zA-Z|
|アルファベット、または、数字|ns::alnum|a-zA-Z0-9|
|数字|ns::digit|0-9|
|表示可能文字|ns::graph|スペース!"#$%&'()=~^¥\\\|{}[]@`*+-/?><,.a-zA-Z0-9|
|アルファベット小文字|ns::lower|a-z|
|アルファベット大文字|ns::upper|A-Z|
|句読|ns::punct|!"#$%&'()*+,-./:;<=>?@[\\]^_`{\|}~|
|ブランク|ns::blank|スペース、タブ|
|スペース|ns::space|スペース、タブ、CR、LF|　
|16進文字|ns::xdigit|0-9a-fA-F|

名前空間の指定により文字判定の実装が異なります。判定のコードは、std::isalpha といった locale のコードに依存します。
localeの実装は、各プラットフォームが提供するライブラリに依存します。
Visual C++ の DEBUGバージョンでは ASSERT マクロにより isalpha 系の関数呼び出しが qi::standardでutf-8のコードを通すと範囲チェックエラーになります。
このように実装がデリケートなので、必要な分類は ns::blank, ns::space を除いて自分で記述した方が良いでしょう。 
漢字を指定したい場合には、ここに文字分類パーサでは足りず、専用のルールを記述する必要があります。
  

