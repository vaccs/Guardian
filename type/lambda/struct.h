
#include "../struct.h"

struct lambda_type
{
	struct type super;
	
	struct type_list* parameters;
	
	struct type* rettype;
};



