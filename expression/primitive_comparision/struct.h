
#include "../struct.h"

#include "kind.h"

struct primitive_comparision_expression
{
	struct expression super;
	
	enum comparison_kind kind;
	
	struct expression* left, *right;
	
	struct type* type;
};
