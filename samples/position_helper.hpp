#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

/**
 * ファイルのエラー箇所を報告できるようにするための
 * postion_iterator の型定義
 */
typedef std::istreambuf_iterator<char> base_iterator_type;
typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
typedef boost::spirit::classic::position_iterator2<forward_iterator_type> pos_iterator_type;

/// stream に対して、ファイルエラー箇所を報告できるようにするためのマクロ
#define BOOST_SPIRIT_POS_ITERATOR( input_stream ) \
  base_iterator_type in_begin(input_stream); \
  base_iterator_type in_end; \
  forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin); \
  forward_iterator_type fwd_end = boost::spirit::make_default_multi_pass(in_end); \
  pos_iterator_type position_begin(fwd_begin, fwd_end, ""); \
  pos_iterator_type position_end; 

#define BOOST_SPIRIT_POS_ITERATOR_FNAME( input_stream, fname ) \
  base_iterator_type in_begin(input_stream); \
  base_iterator_type in_end; \
  forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin); \
  forward_iterator_type fwd_end = boost::spirit::make_default_multi_pass(in_end); \
  pos_iterator_type position_begin(fwd_begin, fwd_end, fname); \
  pos_iterator_type position_end; 

