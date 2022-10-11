
#include "../struct.h"

struct fieldaccess_expression
{
	struct expression super;
	
	struct expression* object;
	
	struct string* fieldname;
};

