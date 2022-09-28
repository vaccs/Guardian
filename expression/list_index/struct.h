
#include "../struct.h"

struct list_index_expression
{
	struct expression super;
	
	struct expression* list;
	
	struct expression* index;
};

