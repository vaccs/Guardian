
#include <enums/assertion_kind.h>

#include "../struct.h"

struct assert_statement
{
	struct statement super;
	
	enum assertion_kind kind;
	
	struct expression* expression;
};

