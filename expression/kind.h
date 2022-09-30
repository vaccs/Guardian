
#ifndef ENUM_EXPRESSION_KIND
#define ENUM_EXPRESSION_KIND

enum expression_kind
{
	ek_len,
	ek_list,
	ek_lambda,
	ek_literal,
	ek_int_math,
	ek_variable,
	ek_funccall,
	ek_comparison,
	ek_list_index,
	ek_parenthesis,
};

#endif
