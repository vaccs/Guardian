
#include "../struct.h"

#include "kind.h"

struct comparison_expression
{
	struct expression super;
	
	enum comparison_expression_kind kind;
	
	struct expression* left, *right;
};
