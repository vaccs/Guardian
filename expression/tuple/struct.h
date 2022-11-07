
#include "../struct.h"

struct tuple_expression
{
	struct expression super;
	
	struct expression_list* subexpressions;
};

