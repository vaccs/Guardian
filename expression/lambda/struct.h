
#include "../struct.h"

struct lambda_expression
{
	struct expression super;
	
	struct parameter_list* parameters;
	
	struct unresolved* captured;
	
	struct expression* body;
	
	unsigned id;
};

