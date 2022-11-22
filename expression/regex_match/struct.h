
#include "../struct.h"

struct regex_match_expression
{
	struct expression super;
	
	struct expression* expression;
	
	struct regex* regex;
};

