
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/struct.h>
#include <out/function_queue/submit_lambda_new.h>

/*#include <parameter/struct.h>*/

#include <list/parameter/foreach.h>

#include <type_cache/get_type/environment.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* outer_environment)
{
	ENTER;
	
	assert(super->kind == ek_lambda);
	
	struct lambda_expression* this = (void*) super;
	
	struct avl_tree_t* environment_tree = avl_alloc_tree(compare_named_types, free_named_type);
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			dpvs(name);
			
			struct named_type* ntype = new_named_type(name, type);
			
			void* ptr222 = avl_insert(environment_tree, ntype);
			
			assert(ptr222);
		}
		runme;
	}));
	
	struct environment_type* environment =
		type_cache_get_environment_type2(shared->tcache, outer_environment, environment_tree);
	
	type_queue_submit(shared->tqueue, (struct type*) environment);
	
	dpv(environment);
	
	this->environment = environment;
	this->id = shared->fqueue->lambda_id++;
	
	unsigned new_id = function_queue_submit_lambda_expression_new(shared->fqueue, this);
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"func_%u(environment)"
	"", new_id);
	
	avl_free_tree(environment_tree);
	
	EXIT;
	return tree;
}










