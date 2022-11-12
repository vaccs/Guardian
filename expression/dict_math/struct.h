
#include "../struct.h"

struct dict_math_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

