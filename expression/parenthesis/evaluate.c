
#include <debug.h>

#include <value/inc.h>

#include "struct.h"
#include "evaluate.h"

struct value* parenthesis_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct parenthesis_expression* this = (void*) super;
	
	TODO;
	
	EXIT;
/*	return result;*/
}
