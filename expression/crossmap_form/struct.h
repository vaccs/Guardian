
#include "../struct.h"

struct crossmap_form_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression_list* arguments;
};

