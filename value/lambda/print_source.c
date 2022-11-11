
#include <stddef.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <scope/foreach.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

/*#include <type/struct.h>*/

#include <out/shared.h>
#include <out/function_queue/struct.h>
/*#include <out/type_queue/submit.h>*/

#include <out/function_queue/submit_lambda_new.h>

#include <type_cache/get_type/environment.h>

/*#include <mpz/struct.h>*/

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct environment_type* _)
{
	ENTER;
	
	assert(super->kind == vk_lambda);
	
	struct lambda_value* this = (void*) super;
	
	struct avl_tree_t* environment_tree = avl_alloc_tree(compare_named_types, free_named_type);
	
	scope_foreach(this->captured, ({
		void runme(struct string* name, struct value* value)
		{
			struct named_type* ntype = new_named_type(name, value->type);
			
			void* ptr222 = avl_insert(environment_tree, ntype);
			
			assert(ptr222);
		}
		runme;
	}));
	
	struct environment_type* environment =
		type_cache_get_environment_type2(shared->tcache, NULL, environment_tree);
	
	dpv(environment);
	
	this->environment = environment;
	this->id = shared->fqueue->lambda_id++;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned new_id = function_queue_submit_lambda_value_new(shared->fqueue, this);
	
	stringtree_append_printf(tree, "func_%u()", new_id);
	
	avl_free_tree(environment_tree);
	
	EXIT;
	return tree;
	
}















