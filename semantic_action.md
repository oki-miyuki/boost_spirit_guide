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

Context, bool& の引数を加える事ができます。
```
C++:semantic action 例3
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <vector>

namespace qi = boost::spirit::qi;

void do_action(const int& n, qi::unused_type ctx, bool& abort) {
  std::cout << n << std::endl;
  if( n > 2 ) abort = false; // ルールをマッチさせない
}

int main() {
	std::string input = "0 1 2 3 4";
	qi::parse( input.begin(), input.end(), *(qi::int_[do_action] % ' ')	);
	return 0;
}
```

## Bind

  関数やアダプタなどを Bind する事ができます。  
  bind系のエラーに遭遇した時は [bind.troubleshooting](https://www.boost.org/doc/libs/1_70_0/libs/bind/doc/html/bind.html#bind.troubleshooting) が参考になります。

std::bind 例    
```
C++:semantic action bind 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <functional>

namespace qi = boost::spirit::qi;

struct foo {
  void do_action(const int& n) {
    std::cout << n << std::endl;
  }
  void parse(const std::string& input) {
    qi::parse( input.begin(), input.end(), 
      qi::int_[std::bind(&foo::do_action, this, std::placeholders::_1)] ); 
  }
};

int main() {
  std::string input = "123";
  foo f;
  f.parse( input );
  return 0;
}
```


