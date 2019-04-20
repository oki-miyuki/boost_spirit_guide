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
