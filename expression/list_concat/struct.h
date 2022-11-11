
#include "../struct.h"

struct list_concat_expression
{
	struct expression super;
	
	struct expression* left;
	struct expression* right;
};

