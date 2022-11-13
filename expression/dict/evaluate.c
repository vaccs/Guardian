
#include <assert.h>

#include <debug.h>

/*#include <value/free.h>*/
/*#include <value/dict/new.h>*/
/*#include <value/dict/assign.h>*/

#include <pair/value/new.h>
#include <pair/value/free.h>

#include <pair/expression/struct.h>

/*#include <list/expression_pair/struct.h>*/
#include <list/expression_pair/foreach.h>

#include <list/value_pair/new.h>
#include <list/value_pair/append.h>
#include <list/value_pair/free.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* dict_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	assert(super->kind == ek_dict);
	
	struct dict_expression* this = (void*) super;
	
	struct value_pair_list* elements = new_value_pair_list();
	
	expression_pair_list_foreach(this->elements, ({
		void runme(struct expression_pair* epair)
		{
			struct value* key = expression_evaluate(epair->key, scope);
			struct value* val = expression_evaluate(epair->value, scope);
			
			struct value_pair* pair = new_value_pair(key, val);
			
			value_pair_list_append(elements, pair);
			
			free_value_pair(pair);
			free_value(key), free_value(val);
		}
		runme;
	}));
	
	struct value* value = dict_run(super->type, elements);
	
	free_value_pair_list(elements);
	
	EXIT;
	return value;
}













