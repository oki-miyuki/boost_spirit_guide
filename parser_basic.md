# パーサ基本

  ルールは Iterator(入力) と Skipper(コメントなどの入力をスキップするルール) と 解析された値の型(属性) から構成されます。  
  Skipper の説明には基本では触れず、ルールを構築するようになってから取扱います。  

  まずは、文字列の入力から値を取り出すための基本ルールを見て行きましょう。基本ルールの確認は、下記のようなコードで行います。  
  ルールにマッチしない入力は、解析に失敗します(qi::parse が false を返す)。  

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
解析するルールが qi::int_ に相当し、入力文字列は "12345" です。


