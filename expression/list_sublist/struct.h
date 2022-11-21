
#include "../struct.h"

struct list_sublist_expression
{
	struct expression super;
	
	struct expression* list;
	
	struct expression* startindex, *endindex;
};

