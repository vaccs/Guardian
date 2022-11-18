
#include <assert.h>

#include <debug.h>

#include <list/value/new.h>
/*#include <list/value/foreach.h>*/
#include <list/value/append.h>
#include <list/value/free.h>

#include <list/expression/foreach.h>

#include <value/tuple/new.h>
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* tuple_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	assert(super->kind == ek_tuple);
	
	struct tuple_expression* this = (void*) super;
	
	struct value_list* subvalues = new_value_list();
	
	expression_list_foreach(this->subexpressions, ({
		void runme(struct expression* subexpression)
		{
			struct value* subvalue = expression_evaluate(subexpression, scope);
			
			value_list_append(subvalues, subvalue);
			
			free_value(subvalue);
		}
		runme;
	}));
	
	struct value* value = new_tuple_value(super->type, subvalues);
	
	free_value_list(subvalues);
	
	EXIT;
	return value;
}













