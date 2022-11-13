
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>
/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

/*#include <named/type/struct.h>*/
#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <named/expression/struct.h>

#include <list/named_expression/foreach.h>

#include <type_cache/get_type/environment.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>
#include <type/environment/struct.h>

/*#include <parameter/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <type_check/unresolved/foreach.h>*/

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* let_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* outer_environment)
{
	ENTER;
	
	assert(super->kind == ek_let);
	
	struct let_expression* this = (void*) super;
	
	struct avl_tree_t* environment_tree = avl_alloc_tree(
		compare_named_types, free_named_type);
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* parameter)
		{
			struct named_type* ntype = new_named_type(
				parameter->name, parameter->expression->type);
			
			void* ptr = avl_insert(environment_tree, ntype);
			
			assert(ptr);
		}
		runme;
	}));
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct environment_type* environment = 
		type_cache_get_environment_type2(
		shared->tcache, outer_environment, environment_tree);
	
	type_queue_submit(shared->tqueue, (struct type*) environment);
	
	stringtree_append_printf(tree,
		"struct type_%u* prev = environment;",
		outer_environment->super.id);
	
	unsigned new_id = function_queue_submit_new(
		shared->fqueue, &environment->super);
	stringtree_append_printf(tree,
		"struct type_%u* environment = func_%u(prev);",
		environment->super.id, new_id);
	
	// evaluate each one, adding to environment
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* parameter)
		{
			stringtree_append_printf(tree,
				"environment->$%.*s = ",
				parameter->name->len, parameter->name->chars);
			
			struct stringtree* subtree = expression_print_source(
				parameter->expression, shared, environment);
			
			stringtree_append_tree(tree, subtree);
			
			stringtree_append_printf(tree, ";");
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	stringtree_append_printf(tree,
		"struct type_%u* result = ", super->type->id);
	
	struct stringtree* subtree = expression_print_source(
		this->body, shared, environment);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(
		shared->fqueue, (struct type*) environment);
	stringtree_append_printf(tree, "func_%u(environment);", free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(subtree);
	avl_free_tree(environment_tree);
	
	EXIT;
	return tree;
}

















