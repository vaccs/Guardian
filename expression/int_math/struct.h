
#include "../struct.h"

#include "kind.h"

struct int_math_expression
{
	struct expression super;
	
	enum int_math_expression_kind kind;
	struct expression* left, *right;
};
