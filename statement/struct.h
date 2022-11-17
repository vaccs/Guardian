
#include <enums/assertion_kind.h>

#include "kind.h"

struct statement
{
	enum statement_kind kind;
	
	enum assertion_kind assertion_kind;
	
	struct string* name;
	
	struct expression* expression;
	
	unsigned refcount;
	
	unsigned line;
};

