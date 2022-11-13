
#include "../struct.h"

struct lambda_expression
{
	struct expression super;
	
	struct parameter_list* parameters;
	
	struct expression* body;
	
	struct environment_type* environment;
	
	unsigned id; // gotten from function_queue
};


