
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <named/expression/struct.h>

#include <list/named_expression/foreach.h>

#include <avl/insert.h>

#include <named/type/new.h>

#include <value/free.h>

#include <type_cache/get_environment_type.h>

#include <value/struct.h>

#include <value/environment/new.h>

#include <value/environment/declare.h>

#include <value/environment/assign.h>

#include <avl/free_tree.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* let_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* outside)
{
	ENTER;
	
	assert(super->kind == ek_let);
	
	struct let_expression* this = (void*) super;
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* nexpression)
		{
			struct named_type* ntype = new_named_type(nexpression->name, nexpression->expression->type);
			
			void* ptr = avl_insert(types, ntype);
			
			assert(ptr);
		}
		runme;
	}));
	
	struct type* type = type_cache_get_environment_type2(tcache, outside->type, types);
	
	struct value* environment = new_environment_value(type, outside);
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* nexpression)
		{
			environment_value_declare(environment, nexpression->name, NULL);
		}
		runme;
	}));
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* nexpression)
		{
			struct value* value = expression_evaluate(
				tcache, nexpression->expression, environment);
			
			environment_value_assign(environment, nexpression->name, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* result = expression_evaluate(tcache, this->body, environment);
	
	free_value(environment);
	
	avl_free_tree(types);
	
	EXIT;
	return result;
	
}











	
	
	
	
	
	
	
	
	
	
	
	
