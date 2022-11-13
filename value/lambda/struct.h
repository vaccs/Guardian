
#include "../struct.h"

struct lambda_value
{
	struct value super;
	
	struct parameter_list* parameters;
	
	struct scope* captured;
	
	struct expression* body;
	
	struct environment_type* captured_type;
	
	unsigned id; // gotten from function_queue
};

