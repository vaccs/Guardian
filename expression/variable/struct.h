
#include "../struct.h"

#include "kind.h"

struct variable_expression
{
	struct expression super;
	
	enum variable_expression_kind kind;
	
	struct string* name;
};

