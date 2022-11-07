
#include "../struct.h"

struct tuple_concat_expression
{
	struct expression super;
	
	struct expression* left, *right;
};
