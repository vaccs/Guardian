
#include "../struct.h"

struct isexecutableby_form_expression
{
	struct expression super;
	
	struct expression* path;
	
	struct expression* user;
};

