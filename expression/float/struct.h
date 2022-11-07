
#include "../struct.h"

struct float_expression
{
	struct expression super;
	
	struct expression* subexpression;
};

