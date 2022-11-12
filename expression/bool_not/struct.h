
#include "../struct.h"

struct bool_not_expression
{
	struct expression super;
	
	struct expression* subexpression;
};

