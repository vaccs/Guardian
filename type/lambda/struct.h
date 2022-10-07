
#include "../struct.h"

struct lambda_type
{
	struct type super;
	
	struct parameter_list* parameters;
	
	// somehow include all of the types and names of all the captured values
	// of all the lambda expressions or values of this type?
	
	struct type* rettype;
};



