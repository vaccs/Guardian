
#include "../struct.h"

struct product_expression
{
	struct expression super;
	
	struct expression* list;
};

