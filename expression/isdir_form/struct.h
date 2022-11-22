
#include "../struct.h"

struct isdir_form_expression
{
	struct expression super;
	
	struct expression* path;
};

