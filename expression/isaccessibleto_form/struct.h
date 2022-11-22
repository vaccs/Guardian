
#include "../struct.h"

struct isaccessibleto_form_expression
{
	struct expression super;
	
	struct expression* path;
	
	struct expression* user;
};

