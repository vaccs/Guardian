
#ifndef ENUM_INT_MATH_EXPRESSION_KIND
#define ENUM_INT_MATH_EXPRESSION_KIND

enum int_math_expression_kind
{
	imek_negate,
	
	imek_add,
	imek_subtract,
	imek_multiply,
	imek_rdivide,
	imek_qdivide,
	imek_expo,
	
	imek_bitnot,
	imek_bitand,
	imek_bitior,
	imek_bitxor,
	
	imek_lshift,
	imek_rshift,
};

#endif
