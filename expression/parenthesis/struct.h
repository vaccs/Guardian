
#include "../struct.h"

struct parenthesis_expression
{
	struct expression super;
	
	struct expression* expression;
};

