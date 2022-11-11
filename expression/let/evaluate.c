
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <scope/new.h>
#include <scope/declare.h>
#include <scope/assign.h>
#include <scope/free.h>

#include <named/expression/struct.h>

#include <list/named_expression/foreach.h>

#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* let_expression_evaluate(
	struct expression* super,
	struct scope* outside)
{
	ENTER;
	
	assert(super->kind == ek_let);
	
	struct let_expression* this = (void*) super;
	
	struct scope* scope = new_scope(outside);
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* nexpression)
		{
			scope_declare(scope, nexpression->name, NULL);
		}
		runme;
	}));
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* nexpression)
		{
			struct value* value = expression_evaluate(
				nexpression->expression, scope);
			
			scope_assign(scope, nexpression->name, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* result = expression_evaluate(this->body, scope);
	
	free_scope(scope);
	
	EXIT;
	return result;
}











	
	
	
	
	
	
	
	
	
	
	
	
