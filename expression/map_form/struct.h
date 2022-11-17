
#include "../struct.h"

struct map_form_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression_list* arguments;
};

