
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "evaluate.h"

struct value* logical_and_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	struct logical_and_expression* this = (void*) super;
	
	struct value* value = scope_lookup(scope, this->name);
	
	EXIT;
	return value;
	#endif
}
