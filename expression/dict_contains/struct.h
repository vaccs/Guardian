
#include "../struct.h"

struct dict_contains_expression
{
	struct expression super;
	
	struct expression* dict;
	struct expression* key;
};

