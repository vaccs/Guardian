
#include "../struct.h"

struct list_expression
{
	struct expression super;
	
	struct expression_list* elements;
};

