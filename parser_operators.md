# パーサ・オペレータ

ルールを記述する上で一番重要なのがオペレータです。
重要だと思う順に記述します。表中の *A* , *B* はパーサを示します。

| オペレータ | モデル | 説明 |
|:--|:--|:--|
| \**A* | UnaryParser | 0回以上 *A* にマッチする |
| +*A* | UnaryParser | 1回以上 *A* にマッチする |
| *A* \| *B* | NaryParser | *A* または *B* にマッチする |
| *A* >> *B* | NaryParser | *A* にマッチした次に *B* にマッチする。*B* にマッチしなかった場合 *A* まで巻き戻る事ができる |
| *A* > *B* | NaryParser | *A* にマッチした次に *B* にマッチする。*B* にマッチしなかった場合、*A* には戻れない |
| *A* - *B* | NaryParser | *A* にマッチする中から *B* にマッチするケースを取り除く |
| *A* % *B* | BinaryParser | \*(*A* % *B*) といった使い方をし、*B* は区切り記号のパーサである。配列要素 1,2,...,n を表現するためのパーサ |
| -*A* | UnaryParser | 0回または1回 *A* にマッチする |
| !*A* | UnaryParser | *A* にマッチしないパーサ。値は取り出せない |
| &*A* | UnaryParser | *A* にマッチするパーサ。値は取り出せない |  
| *A* \|\| *B* | NaryParser | *A* に0回または1回マッチし、*B* に0回または1回マッチする。ただし *A* と *B* 共にマッチしない場合を除く |
| *A* ^ *B* | NaryParser | *A* と *B* は、それぞれ0回または1回マッチし、かつ、*A* と *B* のマッチする順序は問わない |  

```
C++: *( A % B )
#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345 223  54321";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), *( qi::int_ % +qi::standard::blank), v ); 
	for(int n: v) { std::cout << n << std::endl; }
	return 0;
}
```

```
C++: A >> B
#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345 223  54321";
	std::vector<int> v;
	qi::parse( input.begin(), input.end(), *( qi::int_ % +qi::standard::blank_), v ); 
	for(int n: v) { std::cout << n << std::endl; }
	return 0;
}
```
