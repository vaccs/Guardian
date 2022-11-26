
#include "../struct.h"

struct string_concat_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

