# 補助パーサ
  補助のパーサが用意されています。(namespace qi = boost::spirit::qi)
  
| 型(属性) | ルール | 説明 |
|:--|:--|:--|
|qi::unused_type|qi::eol| CRLF または CR または LF にマッチします。|
|qi::unused_type|qi::eoi| 入力 Iterator が first == last になった時にマッチします。|
|qi::unused_type|qi::eps| 必ずマッチします。|
|qi::unused_type|qi::eps(cond)| bool型 cond が true の場合マッチします。|
|任意の型|qi::lazy(value)|


