
#include "../struct.h"

struct string_slice_expression
{
	struct expression super;
	
	struct expression* string;
	
	struct expression* startindex, *endindex;
};

