
#include "../struct.h"

struct map_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression_list* arguments;
};

