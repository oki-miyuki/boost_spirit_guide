# 補助パーサ
  補助のパーサが用意されています。(namespace qi = boost::spirit::qi)
  
| 型(属性) | ルール | 説明 |
|:--|:--|:--|
|qi::unused_type|qi::eol| CRLF または CR または LF にマッチします。|
|qi::unused_type|qi::eoi| 入力 Iterator が first == last になった時にマッチします。|
|qi::unused_type|qi::eps| 必ずマッチします。|
|qi::unused_type|qi::eps(_cond_)| bool型 cond が true の場合マッチします。|
|任意の型|qi::lazy(_rule_)| rule の属性をインスタンス化し値として取り出す。 |
|任意の型| _rule_| qi::lazy(_rule_) に同じ。 |
|任意の型| qi:attr(_value_) | 直接値を取り出す。(ruleを経由しない) |

  qi::eps は、後述するセマンティック・アクションと組み合わせて使用します。  
  qi::lazy(_rule_) は、特に意識する必要はありません。  
  
qi::attr サンプル
```
C++: qi::attr 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

int main() {
	std::string input = "one two three";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), 
	  *(
	    (
    	   (qi::lit("one") > qi::attr(1)) 
	    | (qi::lit("two") > qi::attr(2)) 
	    | (qi::lit("three") > qi::attr(3))
	    ) % qi::standard::blank
	   ), 
	   v 
	 );
	for( int n : v ) { std::cout << n << std::endl; }
	return 0;
}
```
  qi::attr(_value_) は、ルールに応じて値を設定する場合に使用できます。
