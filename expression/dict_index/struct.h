
#include "../struct.h"

struct dict_index_expression
{
	struct expression super;
	
	struct expression* dict;
	
	struct expression* index;
};

