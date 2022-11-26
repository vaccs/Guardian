
#include "../struct.h"

struct lambda_expression
{
	struct expression super;
	
	struct named_type_list* parameters;
	
	struct expression* body;
	
	struct type* environment;
	
	unsigned id; // gotten from function_queue
};


