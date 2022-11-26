
#include "../struct.h"

struct filter_form_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression* list;
};

