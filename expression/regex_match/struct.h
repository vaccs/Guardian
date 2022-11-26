
#include "../struct.h"

struct regex_match_expression
{
	struct expression super;
	
	struct expression* string;
	
	struct regex* regex;
};

