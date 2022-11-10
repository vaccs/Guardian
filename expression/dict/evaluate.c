
#include <assert.h>

#include <debug.h>

#include <value/free.h>
#include <value/dict/new.h>
#include <value/dict/set.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/struct.h>
#include <list/expression_pair/foreach.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* dict_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	assert(super->kind == ek_dict);
	
	struct dict_expression* this = (void*) super;
	
	struct value* value = new_dict_value(super->type);
	
	expression_pair_list_foreach(this->elements, ({
		void runme(struct expression_pair* pair)
		{
			struct value* key = expression_evaluate(pair->first, scope);
			struct value* val = expression_evaluate(pair->second, scope);
			
			dict_value_set(value, key, val);
			
			free_value(key), free_value(val);
		}
		runme;
	}));
	
	EXIT;
	return value;
}













