
#include "../struct.h"

struct string_index_expression
{
	struct expression super;
	
	struct expression* string;
	
	struct expression* index;
};

