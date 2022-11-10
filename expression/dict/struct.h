
#include "../struct.h"

struct dict_expression
{
	struct expression super;
	
	struct expression_pair_list* elements;
};

