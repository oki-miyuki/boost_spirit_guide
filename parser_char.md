# 文字パーサ

## 基本
 
### char型

  ルールは char_ になりますが、想定する文字コードに応じて名前空間が異なります。(namespace qi = boost::spirit::qi)
 * qi::ascii
 * qi::iso8859_1
 * qi::standard
 * qi::standard_wide
 
  この辺の設計は流動的ですので、standard, standard_wide の２つを押さえておけば問題ありません。  
  ascii 及び [iso8859_1](https://ja.wikipedia.org/wiki/ISO/IEC_8859-1) は、standard に含まれます。  
  shift_jis, euc_jp という名前空間は存在しませんが、standard に含まれます。  
  utf-8 は standard に含まれます。ただし、utf-8 を iostream の codecvt を経由して wchar_t で処理する場合は standard_wide に含まれます。
 
| 文字型(属性) | ルール | 説明 |
|:--|:--|:--|
|char|qi::standard::char_| 1文字にマッチします。 |
|wchar_t|qi::standard_wide::char_| 1文字ワイド・キャラにマッチします。 |


１文字読み込む(char版) 
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


１文字読み込む(wchar_t版) 
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

### charリテラル

| 文字型(属性) | ルール | サンプル | 説明 |
|:--|:--|:--|:--|
|qi::unused_type | qi::lit(1文字キャラ値) | qi::lit('X') | 1文字値にマッチします。|
|qi::unused_type | qi::lit(1文字ワイドキャラ値) | qi::lit(L'X') | 1文字ワイドキャラ・リテラルにマッチします。|

  qi::unused_type とは、属性においては値として取り出されない型を示します。  

### 文字列リテラル

| 文字型(属性) | ルール | サンプル | 説明 |
|:--|:--|:--|:--|
|qi::unused_type |qi::lit(文字列)| qi::lit("固定文字列") | 指定された文字列にマッチします。|
|qi::unused_type |qi::lit(ワイドキャラ文字列)| qi::lit(L"固定文字列") | 指定されたワイドキャラ文字列にマッチします。|

文字列定数と同じかチェックする(char版)
```
c++:文字列定数 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
  std::string input = "こんにちは"; // Windows では SJIS解釈、他では UTF-8解釈
  auto s = input.begin();
  auto e = input.end();
  qi::parse( s, e, qi::lit("こんにちは") );
  //qi::parse( s, e, qi::lit("こんにちわ") );
  std::cout << ((s == e) ? "マッチ" : "エラー") << std::endl;
  return 0;
}
```
  qi::parse に渡されるイテレータは入力値の解析範囲を示します。  
  引数の開始位置は参照渡しで、解析後にマッチが完了できた位置になっています。  
  s == e ならば、フルマッチを示し、s != e ならば、マッチしなかった事を示します。  
  コメントアウトされた行で解析をすると、結果がマッチからエラーに変わります。　　

### 文字列

| 文字型(属性) | ルール | サンプル |
|:--|:--|:--|
|std::string|+(qi::standard::char_)||
|std::wstring|+(qi::standard_wide::char_)||

  _ここでルールに + という記号が登場しました。_ ルールに適応できる演算子で、1回以上の繰り返しを示します。  
  似た演算子で * という0回以上の繰り返しを示すものもあります。  
  正規表現では同じ意味を持つ + * は後置演算子ですが、C++ の文法で実現するために前置演算子として実装されています。  
  char型の繰り返しをstring型として取り出せるところが巧妙です。  

文字列を取り出す(wchar_t版)
```
c++:文字列定数2 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
  std::wstring input = L"こんにちは";
  std::wstring n;
  qi::parse( input.begin(), input.end(), +qi::standard_wide::char_, n );
  std::wcout.imbue(std::locale(""));
  std::wcout << n << std::endl;
  return 0;
}
```


## 文字条件指定
  qi::standard::char_, qi::standard_wide::char_ に対してマッチする文字を指定する事が可能です。  
 ２通りの指定方法があります

### 開始から終了までの範囲指定

| 引数 | 説明 | 例 |
|:--|:--|:--|
| qi::standard::char_( char arg1, char arg2 ) | arg1: 開始文字, arg2: 終了文字, 開始文字から終了文字までの文字にマッチする | qi::standard::char_('A','Z'); |
| qi::standard_wide::char_( wchar_t arg1, wchar_t arg2 ) | arg1: 開始文字, arg2: 終了文字, 開始文字から終了文字までの文字にマッチする | qi::standard_wide::char_(L'A', L'Z'); |


文字範囲指定された文字列を取り出す
```
c++:範囲指定 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
  std::string input = "FBIJHCBFIJXXX";
  std::string n;
  qi::parse( input.begin(), input.end(), +qi::standard::char_('A', 'J'), n );
  std::cout << n << std::endl; // Xはルールにマッチしないので FBIJHCBFIJ まで表示されます
  return 0;
}
```
  文字の範囲指定で、SJIS、UTF-8(ASCII以外の文字)は指定できません。  
  それでは qi::standard_wide の wchar_t でなら指定できるでしょうか？  
  「答えは半分は解決できるが、根本的には解決しない」です。  
  異体字などUNICODEの定義は複雑で単純に範囲でくくれるような代物ではありません。  

  _ASCII以外の文字の取扱いは、後で説明します。_

### 書式による文字指定

| 引数 | 説明 | 例 |
|:--|:--|:--|
| qi::standard::char_( const char* arg ) | arg: 文字指定 | qi::standard::char_("A-Z"); |
| qi::standard_wide::char_( const wchar_t* arg ) | arg: 文字指定 | qi::standard_wide::char_(L"a-fA-F0-9"); |

  文字指定には、指定したい文字を列挙します。ただし - 文字は先頭で指定する必要があり、２番目以降に出現した場合は - の前後の文字範囲を指定した事になります。  
  "A-Z" の場合、AからZの範囲の文字を指定した事になります。  


文字指定された文字列を取り出す
```
c++:文字指定(個別に文字を指定) 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
  std::wstring input = L"FBIJHABFIJXXX";
  std::wstring n;
  qi::parse( input.begin(), input.end(), +qi::standard_wide::char_(L"ABFHIJ"), n );
  std::wcout.imbue(std::locale(""));
  std::wcout << n << std::endl;
  return 0;
}
```

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
  このように実装がデリケートなので、必要な分類は ns::blank, ns::space を除いて自分で記述した方が良いかもしれません。   

  漢字を指定したい場合には、これら文字分類パーサでは足りず、専用のルールを記述する必要があります。  
  

