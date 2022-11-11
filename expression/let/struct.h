
#include "../struct.h"

struct let_expression
{
	struct expression super;
	
	struct named_expression_list* parameters;
	
	struct expression* body;
};

