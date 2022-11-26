
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <value/environment/lookup.h>

#include "struct.h"
#include "evaluate.h"

struct value* variable_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct variable_expression* this = (void*) super;
	
	struct value* value = environment_value_lookup(environment, this->name);
	
	if (!value)
	{
		// in case a let pushed a NULL
		TODO;
		exit(1);
	}
	
	EXIT;
	return value;
}
