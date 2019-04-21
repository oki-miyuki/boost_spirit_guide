# ルールを書く

　パーサ基本を習得すれば、ルールを記述し構文(grammar)を構築する下地が整ったと言えます。  
  パーサを組み合わせてルールを構築し、ルールを組み合わせて構文(grammar)を構築します。  
  
  以降、解析には、parse ではなく、Skipper を指定できる phrase_parse 関数を使用していきます。  
  また、  
  namespace qi = boost::spirit::qi;  
  namespace ph = boost::pheonix;  
  は省略していきます。    

```
  template <typename Iterator, typename Expr, typename Skipper,   
      typename Attr1, typename Attr2, ..., typename AttrN>  
  inline bool phrase_parse(  
	  Iterator& first, Iterator last,  
    const Expr& expr,  
    const Skipper& skipper,  
    Attr1& attr1, Attr2& attr2, ..., AttrN& attrN  
  );  
```

応用のコード
```
c++:応用のコード
#include <boost/spirit/include/qi.hpp>  // boost::spirit::qi を利用します
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;  // namespaceが長いので qi にします

// 構文を構築します。
// 本ガイドでは、構文に Iterator, Skipper のパラメータのみを扱います
// Iterator と Skipper が交換可能な状態で作成します。
template <typename Iterator, typename Skipper>
struct my_grammar 
  // 返される値(属性)は int なので int のインスタンス関数型を指定します 
  : qi::grammar<Iterator, int(), Skipper>
{
  // 構文の内部で使用するルールのメンバ変数
  qi::rule<Iterator, int(), Skipper>  start_;
  // ベース型である qi::grammar に渡す開始ルールは、
  // qi::grammar<Iterator, int(), Skipper> と同様に
  // テンプレート・パラメータを一致させて(qi::rule<Iterator,int(),Skipper>)おく必要があります。
  my_grammar() : my_grammar::base_type(start_, "my_grammar") {
    start_ = qi::int_; // スタートのルールを記述します(パーサ基本の通り)。
  }
};

int main() {
  std::string input = "12345"; // 解析させる入力です。値を書き換えて遊んでください
  int n;  // 解析された結果を格納するための変数です。この部分は記述する構文に応じて変わります。
  my_grammar<
    std::string::iterator,    // Iterator 型を具体的に指定します
    qi::standard::space_type  // Skipper として qi::standard::space に対応するインスタンス関数型
  > myg; // 構文
  qi::phrase_parse( // 解析をする関数本体です
    input.begin(), input.end(), // 解析させる入力の指定 
    myg, // 解析するルール、または、構文
    qi::standard::space, // スキップするルール、または、構文
    // myg の Skipper 宣言と辻褄が合わせないといけません。
    // qi::standard::space => (スペース|タブ|CR|LF）にマッチ
    n // 解析された結果を格納するための変数
  ); 
  std::cout << n << std::endl; // 解析された結果を確認します。
  return 0;
}
```

## ルール

  パーサ基本で触れたように、ルールは Iterator(入力) と Skipper(コメントなどの入力をスキップするルール) と 解析された値の型(属性) から構成されます。

  qi::rule は、  
```
  template <typename Iterator, typename A1, typename A2, typename A3>  
  qi::rule<Iterator, A1, A2, A3>  
```
  Iterator はイテレータ、A1, A2, A3 は、Signature、Skipper, Locals の何れかです。
  A1...A3 は boost::mpl::vector により実装されています。

| template parameter | 説明 |
|:--|:--|
| Iterator | 入力値のイテレータ型です。 |
| Signature | ルールの値型(属性)です。何も返したくない場合 qi::unused_type() を指定します。それ以外は インスタンス関数型を指定します。|
| Skipper | コメントの文法(ルール)を指定します。Iterator 型は同じでなければなりません。|
| Locals | ローカルのプリミティブ型集合です。難しいので、ここでは扱いません。|

```
C++: ルール例
qi::rule<Iterator, std::string(), Skipper> str_rule = +qi:char_("A-Za-z0-9");
qi::rule<Iterator, std::vector<int>, Skipper> nums_rule = *(qi::int_ % ',');
qi::rule<Iterator, qi::unused_type(), Skipper> foo_rule = "foo(" >> str_rule >> ':' >> nums_rule >> ')';
```

## 構文(grammar)

  ルールをまとめて構文を構築します。構文もルール同様 Iterator(入力) と Skipper(コメントなどの入力をスキップするルール) と 解析された値の型(属性) から構成されます。  
  qi::grammar を継承する形で構文を構築します。  

  本ガイドでは、Iterator と Skipper を交換可能な形で実装していきます。  
```
  template <typename Iterator, typename Skipper>
  struct my_grammar : qi::grammar<Iterator, SIGNATURE, Skipper> {
    my_grammar() : my_grammar::base_type<Iterator, SIGNATURE, Skipper>( start_, "my_grammar" ) {
      start_ = ...;
    }
    qi::rule<Iterator, SIGNATURE, Skipper> start_;
  };
```

  SIGNATURE は、構文の値型(属性)です。インスタンス関数型を指定します。  
  注意点として、grammar の SIGNATURE と、base_type の コンストラクタに引き渡す qi::rule の SIGNATURE が一致している必要があります。  



