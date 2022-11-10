
#include "../struct.h"

struct lambda_expression
{
	struct expression super;
	
	struct parameter_list* parameters;
	
	struct type* environment;
	
	struct expression* body;
	
	unsigned id; // gotten from function_queue
};

