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
ブランク(スペース・タブ)で区切られた数値を取り出す

```
C++: A >> B
#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345,abcd,54321";
	int n, m;
	std::string s;
	qi::parse( input.begin(), input.end(), 
	  qi::int_ >> ',' >> +(qi::standard::char_ - ',') >> ',' >> qi::int_,
	  n, s, m ); 
	std::cout << n << "," << s << "," << m << std::endl;
	return 0;
}
```
qi::lit(',') は implicit conversion(暗黙の型変換)により ',' と省略して記述する事ができます。
ただし、後述するセマンティック・アクションを適応する場合は、'A'[action] と省略形で記述するとコンパイルエラーになるので気をつけましょう。
+(qi::standard::char_ - ',') は、','以外の文字から構成される文字列にマッチします。

```
C++: A > B
#include <boost/spirit/include/qi.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "dog(2pochi),cat(tama)";
	std::vector<std::string> v;
	qi::parse( input.begin(), input.end(), 
	  *( 
	    (
	     //("dog(" >> +qi::standard::char_("a-z")  >> ')')
	     ("dog(" > +qi::standard::char_("a-z")  > ')')
	     | (+qi::omit[qi::standard::alpha] > '(' > +qi::standard::alnum > ')')
	    ) % ','
	  )
	  , v ); 
	for(std::string n: v) { std::cout << n << std::endl; }
	return 0;
}
```
ルール中に出てくる qi::omit は、後述するパーサ・ディレクティブで説明します。
cat を v へ入れたくないので qi::omit で指定しています。
dog( まで解析し、2pochi はアルファベットa-zの範囲外なのでマッチしません。<BR><BR>
コメントアウトされているようにオペレータ >> であれば巻き戻って、| 以降の次のルールで解析する事ができますが、オペレータ > を使用しているため 2pochi に遭遇した段階で解析を終了します。<BR><BR>
\> の記述を >> の記述にして実行すると、巻き戻る事ができ、(+qi::omit[qi::standard::alpha] > '(' > +qi::standard::alnum > ')') のルールで処理されるようになります。



