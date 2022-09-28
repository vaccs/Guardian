
#include "../struct.h"

struct lambda_value
{
	struct value super;
	
	struct parameter_list* parameters;
	
	struct parameter_list* captured;
	
	struct expression* body;
};

