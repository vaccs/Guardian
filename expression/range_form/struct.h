
#include "../struct.h"

struct range_form_expression
{
	struct expression super;
	
	struct expression* start;
	
	struct expression* end;
};

