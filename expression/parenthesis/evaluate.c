
#include <assert.h>

#include <debug.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* parenthesis_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	assert(super->kind == ek_parenthesis);
	
	struct parenthesis_expression* this = (void*) super;
	
	struct value* result = expression_evaluate(this->expression, scope);
	
	EXIT;
	return result;
}
