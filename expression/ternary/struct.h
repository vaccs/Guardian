
#include "../struct.h"

struct ternary_expression
{
	struct expression super;
	
	struct expression* conditional;
	
	struct expression* true_case;
	
	struct expression* false_case;
};

