
#include <assert.h>

#include <debug.h>

#include <scope/lookup.h>

#include "struct.h"
#include "evaluate.h"

struct value* dict_concat_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	struct dict_concat_expression* this = (void*) super;
	
	struct value* value = scope_lookup(scope, this->name);
	
	EXIT;
	return value;
	#endif
}
