
#include "../struct.h"

struct list_contains_expression
{
	struct expression super;
	
	struct expression* element;
	struct expression* list;
};

