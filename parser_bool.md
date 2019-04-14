# boolパーサ
  boolパーサが用意されています。(namespace qi = boost::spirit::qi)  
  組込型として用意されているので、bool型はこちらを使用しましょう。  

| 型(属性) | ルール |
| bool | qi::bool_ | 

```
c++:qi::bool_ 例
#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "true false";
	bool a, b;
	qi::parse( input.begin(), input.end(), qi::bool_ >> ' ' >> qi::bool_, a, b );
	std::cout << a << "," << b << std::endl;
	return 0;
}
```


