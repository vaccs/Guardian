
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <list/named_type/foreach.h>

/*#include <scope/new.h>*/
/*#include <scope/declare.h>*/
/*#include <scope/free.h>*/

/*#include <parameter/struct.h>*/

/*#include <value/lambda/struct.h>*/

/*#include <list/parameter/struct.h>*/

#include <list/value/foreach.h>

/*#include <expression/evaluate.h>*/

#include <list/named_type/struct.h>

#include <list/value/struct.h>

#include <named/type/struct.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <expression/evaluate.h>

#include <value/environment/new.h>
#include <value/environment/struct.h>
#include <value/lambda/struct.h>
#include <avl/insert.h>
#include <value/struct.h>

#include <value/free.h>

#include <type_cache/get_environment_type.h>

#include <value/environment/declare.h>

#include <named/type/inc.h>

/*#include "struct.h"*/

#include "run.h"

struct value* funccall_run(
	struct type_cache* tcache,
	struct lambda_value* lambda,
	struct value_list* arguments)
{
	ENTER;
	
	struct avl_tree_t* layer_variables = avl_alloc_tree(
		compare_named_types, free_named_type);
	
	named_type_list_foreach(lambda->parameters, ({
		void runme(struct named_type* named_type)
		{
			void* ptr = avl_insert(layer_variables, inc_named_type(named_type));
			assert(ptr);
		}
		runme;
	}));
	
	struct type* type = type_cache_get_environment_type2(tcache,
		lambda->captured ? lambda->captured->type : NULL,
		layer_variables);
	
	struct value* environment =
		new_environment_value(type, lambda->captured);
	
	assert(lambda->parameters->n == arguments->n);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct named_type* parameter = lambda->parameters->data[i];
		struct value* value = arguments->data[i];
		
		assert(parameter->type == value->type);
		
		environment_value_declare(environment, parameter->name, value);
	}
	
	// evaluate inner expression
	struct value* retval = expression_evaluate(tcache, lambda->body, environment);
	
	avl_free_tree(layer_variables);
	
	free_value(environment);
	
	EXIT;
	return retval;
}















