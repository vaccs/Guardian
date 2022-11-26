
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include <type_cache/get_bool_type.h>

#include <list/expression/foreach.h>

#include <type/struct.h>
#include <type/lambda/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* filter_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct filter_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	// evaluate lambda:
	{
		struct stringtree* subtree = expression_print_source(
			this->lambda, shared, environment);
		
		stringtree_append_printf(tree, "struct type_%u* lambda = ", this->lambda->type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(subtree);
	}
	
	// evaluate list:
	{
		struct stringtree* subtree = expression_print_source(
			this->list, shared, environment);
		
		stringtree_append_printf(tree, "struct type_%u* list = ", this->list->type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(subtree);
	}
	
	// result:
	{
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "struct type_%u* result = func_%u();", super->type->id, new_id);
	}
	
	// build result:
	{
		struct type* btype = type_cache_get_bool_type(shared->tcache);
		
		unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, btype);
		
		stringtree_append_printf(tree, "for (unsigned i = 0, n = list->n; i < n; i++)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	struct type_%u* conditional = (lambda->evaluate)(lambda, list->data[i]);", btype->id);
		stringtree_append_printf(tree, "	if (conditional->value)");
		stringtree_append_printf(tree, "	{");
		stringtree_append_printf(tree, "		func_%u(result, list->data[i]);", append_id);
		stringtree_append_printf(tree, "	}");
		stringtree_append_printf(tree, "	func_%u(conditional);", free_id);
		stringtree_append_printf(tree, "}");
	}
	
	// free lambda:
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->lambda->type);
		
		stringtree_append_printf(tree, "func_%u(lambda);", free_id);
	}
	
	// free list:
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->list->type);
		
		stringtree_append_printf(tree, "func_%u(list);", free_id);
	}
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














