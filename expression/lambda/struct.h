
#include "../struct.h"

struct lambda_expression
{
	struct expression super;
	
	struct parameter_list* parameters;
	
	struct parameter_list* captured;
	
	struct expression* body;
};

