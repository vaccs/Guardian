
#include <assert.h>

#include <debug.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* parenthesis_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_parenthesis);
	
	struct parenthesis_expression* this = (void*) super;
	
	struct value* result = expression_evaluate(tcache, this->expression, environment);
	
	EXIT;
	return result;
}
