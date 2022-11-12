
#include <assert.h>

#include <debug.h>

/*#include <set/value/new.h>*/
/*#include <set/value/append.h>*/
/*#include <set/value/free.h>*/

/*#include <set/expression/foreach.h>*/

/*#include <value/set/new.h>*/
/*#include <value/free.h>*/

/*#include "../evaluate.h"*/

#include "struct.h"
#include "evaluate.h"

struct value* set_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_set);
	
	struct set_expression* this = (void*) super;
	
	struct value_set* elements = new_value_set();
	
	expression_set_foreach(this->elements, ({
		void runme(struct expression* expression)
		{
			struct value* value = expression_evaluate(expression, scope);
			
			value_set_append(elements, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* value = new_set_value(super->type, elements);
	
	free_value_set(elements);
	
	EXIT;
	return value;
	#endif
}













