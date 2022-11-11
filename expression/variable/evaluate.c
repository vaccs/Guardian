
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <scope/lookup.h>

#include "struct.h"
#include "evaluate.h"

struct value* variable_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct variable_expression* this = (void*) super;
	
	struct value* value = scope_lookup(scope, this->name);
	
	if (!value)
	{
		// in case a let pushed a NULL
		TODO;
		exit(1);
	}
	
	EXIT;
	return value;
}
