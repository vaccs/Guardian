
#include "../struct.h"

struct lambda_value
{
	struct value super;
	
	struct named_type_list* parameters;
	
	struct value* captured;
	
	struct expression* body;
	
	unsigned id; // gotten from function_queue
};

