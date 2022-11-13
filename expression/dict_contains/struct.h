
#include "../struct.h"

struct dict_contains_expression
{
	struct expression super;
	
	struct expression* element;
	struct expression* dict;
};

