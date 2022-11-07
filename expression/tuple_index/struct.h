
#include "../struct.h"

struct tuple_index_expression
{
	struct expression super;
	
	struct expression* tuple;
	
	unsigned index;
};

