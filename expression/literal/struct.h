
#ifndef STRUCT_LITERAL_EXPRESSION
#define STRUCT_LITERAL_EXPRESSION

#include "../struct.h"

struct literal_expression
{
	struct expression super;
	
	struct value* value;
};

#endif
