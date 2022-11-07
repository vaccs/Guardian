
#include "../struct.h"

#include "kind.h"

struct float_math_expression
{
	struct expression super;
	
	enum float_math_expression_kind kind;
	struct expression* left, *right;
};
