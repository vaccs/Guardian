
#include "../struct.h"

struct list_slice_expression
{
	struct expression super;
	
	struct expression* list;
	
	struct expression* startindex, *endindex;
};

