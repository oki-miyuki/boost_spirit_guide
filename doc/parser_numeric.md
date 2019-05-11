# 数値パーサ
  数値型に応じた組み込み型のパーサが用意されています。(namespace qi = boost::spirit::qi)
  
| 数値型(属性) | ルール |
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

