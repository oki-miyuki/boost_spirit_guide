# 補助パーサ
  補助のパーサが用意されています。(namespace qi = boost::spirit::qi)
  
| 型(属性) | ルール | 説明 |
|:--|:--|
|qi::unused_type|qi::eol| CRLF または CR または LF にマッチします。|
|qi::unused_type|qi::eoi| 入力 Iterator が first == last になった時にマッチします。|
|qi::unused_type|qi::eps| 必ずマッチします。|
|qi::unused_type|qi::eps(cond)| bool型 cond が true の場合マッチします。|
|任意の型|qi::lazy(value)|

doubleの値を読み込む
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


floatの値を読み込む
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


unsigned shortの値を読み込む
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

