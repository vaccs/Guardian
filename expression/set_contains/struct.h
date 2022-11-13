
#include "../struct.h"

struct set_contains_expression
{
	struct expression super;
	
	struct expression* element;
	struct expression* set;
};

