
#ifndef ENUM_EXPRESSION_KIND
#define ENUM_EXPRESSION_KIND

enum expression_kind
{
	ek_len,
	ek_has,
	ek_map,
	ek_let,
	ek_sum,
	ek_list,
	ek_dict,
	ek_tuple,
	ek_float,
	ek_lambda,
	ek_literal,
	ek_ternary,
	ek_float_math,
	ek_product,
	ek_int_math,
	ek_variable,
	ek_funccall,
	ek_comparison,
	ek_logical_or,
	ek_list_index,
	ek_fieldaccess,
	ek_parenthesis,
	ek_logical_and,
	ek_tuple_concat,
	ek_tuple_index,
};

#endif
