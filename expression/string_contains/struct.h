
#include "../struct.h"

struct string_contains_expression
{
	struct expression super;
	
	struct expression* substring;
	struct expression* string;
};

