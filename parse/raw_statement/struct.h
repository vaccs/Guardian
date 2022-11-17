
#include <enums/assertion_kind.h>

#include "kind.h"

struct raw_statement
{
	enum raw_statement_kind kind;
	
	enum assertion_kind assertion_kind;
	
	struct string* name;
	
	struct zebu_expression* expression;
	
	unsigned refcount, line;
};

