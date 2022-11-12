
#include "../struct.h"

struct implication_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

