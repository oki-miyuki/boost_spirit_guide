# セマンティック・アクション

  パーサに対して[]オペレータでアクションを記述する事ができます。  
  関数コール、boost::Phoenix による属性値の操作が使用できます。

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
  qi::parse( input.begin(), input.end(), *(qi::int_[do_action] % ' ')  );
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

## Placeholders

  同名の placeholders が存在し、使うライブラリによって名前空間が異なります。  
  placeholders がわからない人は、この説明を飛ばしてかまいません。  
  後で必要と感じた時に読むと理解できると思います。  
  ライブラリと名前空間の対応表を示します。(namespace qi = boost::spirit::qi)  

| ライブラリ | 名前空間 | 例 |
|:--|:--|:--|
| boost::bind | global namespace | ::_1, ::_2, ::_3 |
| std::bind | std::placeholders | std::placeholders::_1 |
| boost::lambda | boost::lambda | boost::lambda::_1 |
| boost::phoenix | qi | qi::_val, qi::_1, qi::_2, qi::_3 |

## Phoenix

  動作や式を埋め込む事ができます。  
  機能が豊富、かつ、説明が難しいのでサンプルを見ていきましょう。  
  namespace qi = boost::spirit::qi;  
  namespace ph = boost::phoenix;  
  
### Phoenix placeholders
  placeholders として使用できるのがルールの属性(出力先)を示す qi::_val と、  
  ルール中のパーサに対応する値 qi::\_1, qi::\_2, ... です。

qi::_val 例
```
C++: qi::_val
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
//namespace ph = boost::phoenix;

int main() {
  std::string input = "2";
  int n;
  qi::parse( input.begin(), input.end(), qi::int_[qi::_val = qi::_1 * 2], n );
  std::cout << n << std::endl;
  return 0;
}
```
  qi::int\_ でパースされた値 qi::\_1 を2倍して、qi::int\_ の属性値として代入しています。  
  qi::\_2 以降は、基本の段階では使用しません。

### Phoenix ref
  変数 variable の参照を ph::ref(variable) で埋め込む事ができます。  

ph::ref 例
```
C++: ph::ref 
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

namespace foo {
  int value_;
}

int main() {
  std::string input = "2";
  qi::parse( input.begin(), input.end(), qi::int_[ph::ref(foo::value_) = qi::_1]   );
  std::cout << foo::value_ << std::endl;
  return 0;
}
```

### Phoenix bind
  class メンバ変数 variable の参照を ph::bind(&class::variable, instance) で埋め込む事ができます。  

ph::bind メンバー変数 例
```
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

struct foo {
  int value_;

  void parse(const std::string& input) {
    qi::parse( input.begin(), input.end(), 
      qi::int_[ph::bind( &foo::value_, this ) = qi::_1 - 1]   );
    std::cout << foo::value_ << std::endl;  
  }
};

int main() {
  std::string input = "2";
  foo f;
  f.parse(input);
  return 0;
}
```

### Phoenix push_back


Phoenix には、他にもたくさんの機能があります。基本では、この辺にしておきます。
