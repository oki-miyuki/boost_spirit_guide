# セマンティック・アクション

  パーサに対して[]オペレータでアクションを記述する事ができます。  
  関数コール、boost::pheonix による属性値の操作が使用できます。

## 関数コール

  ルールの返す値型(属性)の const 参照を引数とする関数を呼び出す事ができます。

属性が qi::unused_type である補助パーサ qi::eps の例
```
C++:semantic action 例1
#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

void do_action1() { std::cout << "hello"; }
void do_action2() { std::cout << " action" << std::endl; }

int main() {
	std::string input = " ";
	qi::parse( input.begin(), input.end(), 
	     qi::eps[do_action1] >> ' ' >> qi::eps[do_action2]
	);
	return 0;
}
```

属性が std::vector\<int\> の例
```
C++:semantic action 例2
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <vector>

namespace qi = boost::spirit::qi;

void do_action(const std::vector<int>& v) { for(int n: v ) { std::cout << n << std::endl; } }

int main() {
	std::string input = "1 2";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), 
	  qi::as<std::vector<int>>()[qi::int_ >> ' ' >> qi::int_][do_action],
	  v
	);
	return 0;
}
```
