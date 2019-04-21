# パーサ・ディレクティブ

  ルールに渡される入力、ルールにより生じる結果。  
  以上を意図的にコントロールするのがディレクティブです。(namespace qi = boost::spirit::qi)  

| ディレクティブ | 説明 |
|:--|:--|
| lexime[] | 直前までSkipルールを適応しスキップさせた上で、Skipルールを適用しないようにします。 |
| no_skip[] | Skipルールを適用しないようにします。|
| no_case[] | アルファベットの大文字小文字の区別を無くします。|
| omit[] | ルールから値を取り出さないようにします。|
| raw[] | 入力シーケンスをそのまま値出力に直結させます。|
| repeat[] | 0回以上繰り返す。* オペレータと同じです。|
| repeat(n)[] | n回繰り返す。|
| repeat(min,max)[] | min回以上、max回以下まで繰り返す。|
| matches[] | マッチしたかどうかをbool値として取り出します。|
| skip[] | leximeまたはno_skipディレクティブ内でSkipルールを再適用します。|
| skip(p)[] | skip ディレクティブに p を Skipルールとして置き換えます。|
| hold[] | ルールの値をキープします。|
| as\<T\>()[] | Tはコンテナ型で、ルール内の値をT型に展開します。直接使用する事はないでしょう。|
| as_string[] | std::string 型へ展開します。直接使用する事はないでしょう。|
| as_wstring[] | std::wstring 型へ展開します。直接使用する事はないでしょう。|
| expect[] | ルールにマッチしない場合はエラーとします。|
 
  Skipper に関するもの no_skip, skip は、後に別途解説します。 
 
raw, repeat サンプル 
```
C++: raw, repeat 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

int main() {
  std::string input = "04142019";
  int year, month, day;
  qi::parse( input.begin(), input.end(), 
       qi::raw[qi::repeat(2)[qi::standard::digit]] 
       >> qi::raw[qi::repeat(2)[qi::standard::digit]] 
       >> qi::raw[qi::repeat(4)[qi::standard::digit]] 
    , month, day, year ); 
  std::cout << year << "/" << month << "/" << day << std::endl;
  return 0;
}
```