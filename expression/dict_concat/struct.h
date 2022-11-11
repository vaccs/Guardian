
#include "../struct.h"

struct dict_concat_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

