
#include "../struct.h"

struct reduce_form_expression
{
	struct expression super;
	
	struct expression* lambda;
	
	struct expression* list;
	
	struct expression* initial;
};

