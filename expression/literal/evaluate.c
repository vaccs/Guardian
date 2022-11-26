
#include <debug.h>

#include <value/inc.h>

#include "struct.h"
#include "evaluate.h"

struct value* literal_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct literal_expression* this = (void*) super;
	
	struct value* result = inc_value(this->value);
	
	EXIT;
	return result;
}
