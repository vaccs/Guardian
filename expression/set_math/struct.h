
#include "../struct.h"

#include "kind.h"

struct set_math_expression
{
	struct expression super;
	
	enum set_math_expression_kind kind;
	
	struct expression* left;
	struct expression* right;
};

