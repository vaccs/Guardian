
#include "../struct.h"

struct has_expression
{
	struct expression super;
	
	struct expression* object;
	
	struct string* fieldname;
};

