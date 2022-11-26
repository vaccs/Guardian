
#include "../struct.h"

struct dict_init_expression
{
	struct expression super;
	
	struct expression_pair_list* elements;
};

