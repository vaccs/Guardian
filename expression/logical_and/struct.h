
#include "../struct.h"

struct logical_and_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

