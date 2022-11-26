
/*#include <value/free.h>*/
/*#include <value/dict_init/new.h>*/
/*#include <value/dict_init/assign.h>*/

/*#include <pair/value/new.h>*/
/*#include <pair/value/free.h>*/

/*#include <pair/expression/struct.h>*/

/*#include <list/expression_pair/struct.h>*/
/*#include <list/expression_pair/foreach.h>*/

/*#include <list/value_pair/new.h>*/
/*#include <list/value_pair/append.h>*/
/*#include <list/value_pair/free.h>*/

/*#include <value/free.h>*/

/*#include "../evaluate.h"*/


#include <assert.h>

#include <debug.h>

#include <list/expression_pair/foreach.h>

#include <list/value_pair/new.h>
#include <list/value_pair/free.h>

#include <expression/evaluate.h>

#include <pair/expression/struct.h>

#include <pair/value/new.h>

#include <list/value_pair/append.h>

#include <value/free.h>

#include <pair/value/free.h>

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* dict_init_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_dict_init);
	
	struct dict_init_expression* this = (void*) super;
	
	struct value_pair_list* elements = new_value_pair_list();
	
	expression_pair_list_foreach(this->elements, ({
		void runme(struct expression_pair* epair)
		{
			struct value* key = expression_evaluate(tcache, epair->key, environment);
			
			struct value* val = expression_evaluate(tcache, epair->value, environment);
			
			struct value_pair* pair = new_value_pair(key, val);
			
			value_pair_list_append(elements, pair);
			
			free_value(key), free_value(val);
			
			free_value_pair(pair);
		}
		runme;
	}));
	
	struct value* value = dict_init_run(super->type, elements);
	
	free_value_pair_list(elements);
	
	EXIT;
	return value;
}













