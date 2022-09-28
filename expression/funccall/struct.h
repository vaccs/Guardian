
#include "../struct.h"

struct funccall_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression_list* arguments;
};

