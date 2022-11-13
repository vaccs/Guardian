
#include "../struct.h"

#include "kind.h"

struct dict_math_expression
{
	struct expression super;
	
	enum dict_math_expression_kind kind;
	
	struct expression* left;
	struct expression* right;
};

