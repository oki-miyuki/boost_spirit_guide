# Boost::Spiritで構文解析
## Boost::Spiritとは
  C++で構文解析を書くためのライブラリです。yacc, lex といったものを使用せず、C++だけで構文解析を行う事ができます。
JSONパーサ、電卓、コンフィグの読み込み、オレオレ・スクリプト、プロトコル・パーサなど、幅広く活用できます。

## このガイドを書いた目的
  このライブラリは、とても面白いのでワクワク感があります。この面白さを伝えたい。と同時に、デリケートな側面もあり、ちょっとした事で心が折れそうになるコンパイルエラーに遭遇したり、挙動に悩まれたりする事があります。Spiritが発表されて、時間がたちました。巷にある情報は古いバージョンのものが多く、情報ソースとしては役に立たないものが増えてきたように思います。日本語の文字列処理を取り扱う情報も少ないので、本ライブラリを本格的に採用するには敷居が高いです。こういったガイドを書ける立場にある人も、自分が思っている以上に少ないのかもしれません。これを書くことによって、世の中にもっと面白いものが出てくる事を願って書きました。

## 本ガイドの進め方
　小さなサンプルを元に理解を深めて行きます。動くコードをかけるようになって、なんぼのものというスタイルです。Spiritの構成として、Qi,Pheonix,Karma,Lex とありますが、Qi と Pheonix のみ扱います。

## パーサ

 * [基本](parser_basic.md)
 * [数値パーサ](parser_numeric.md)
 * [文字パーサ](parser_char.md)
 * [boolパーサ](parser_bool.md)
 * [symbolsパーサ](symbols.md)
 * [パーサ・オペレータ](parser_operators.md)
 * [補助パーサ](parser_auxiliary.md)
 * [パーサ・ディレクティブ](parser_directive.md)
 * [セマンティック・アクション(+フェニックス)](semantic_action.md)
 
## ルール

 * [ルールを書く](rule.md)
 * [Nバイト文字の処理](rule_nbytechars.md)
 * [コメント構文(Skipper)](skipper.md)
 * [構造体を読む(Fusion)](fusion.md)
 * [std::pairを利用する(Fusion)](fusion2.md)
 * [エラー箇所の表示(PositionIterator)](position_iterator.md)
 * [数値パーサ2](parser_numeric2.md)
 * [フェニックスとプレースホルダ](phoenix2.md)