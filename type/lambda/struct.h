
#include "../struct.h"

struct lambda_type
{
	struct type super;
	
	struct parameter_list* parameters;
	
	struct type* rettype;
};



