
#include <debug.h>

#include <value/inc.h>

#include "struct.h"
#include "evaluate.h"

struct value* literal_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct literal_expression* this = (void*) super;
	
	struct value* result = inc_value(this->value);
	
	EXIT;
	return result;
}
