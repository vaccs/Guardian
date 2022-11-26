
#include <assert.h>

#include <debug.h>

#include <type/list/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

/*#include <type/struct.h>*/

#include <type_cache/get_int_type.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_slice_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_list_slice);
	
	struct list_slice_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	struct type* list_type = this->list->type;
	type_queue_submit(shared->tqueue, list_type);
	
	{
		struct stringtree* subtree = expression_print_source(this->list, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* list = ", list_type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	struct type* index_type = type_cache_get_int_type(shared->tcache);
	type_queue_submit(shared->tqueue, index_type);
	
	if (this->startindex)
	{
		struct stringtree* subtree = expression_print_source(this->startindex, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* start = ", index_type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
		
		stringtree_append_printf(tree, ""
			"unsigned native_start;"
			""
			"if (mpz_fits_uint_p(start->value) && (native_start = mpz_get_ui(start->value)) > list->n)"
			"{"
				"fprintf(stderr, \"%%s: cannot generate slice starting from index %%u in list %%u elements long!\\n\", argv0, native_start, list->n);"
				"exit(1);"
			"}"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->startindex->type);
		stringtree_append_printf(tree, "func_%u(start);", free_id);
	}
	else
	{
		stringtree_append_printf(tree, "unsigned native_start = 0;");
	}
	
	if (this->endindex)
	{
		struct stringtree* subtree = expression_print_source(this->endindex, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* end = ", index_type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
		
		stringtree_append_printf(tree, ""
			"unsigned native_end;"
			""
			"if (mpz_fits_uint_p(end->value) && (native_end = mpz_get_ui(end->value)) > list->n)"
			"{"
				"fprintf(stderr, \"%%s: cannot generate slice ending on index %%u in list %%u elements long!\\n\", argv0, native_end, list->n);"
				"exit(1);"
			"}"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->endindex->type);
		stringtree_append_printf(tree, "func_%u(end);", free_id);
	}
	else
	{
		stringtree_append_printf(tree, "unsigned native_end = list->n;");
	}
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	stringtree_append_printf(tree, "struct type_%u* result = func_%u();", super->type->id, new_id);
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
	stringtree_append_printf(tree, "for (unsigned index = native_start; index < native_end; index++)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	func_%u(result, list->data[index]);", append_id);
	stringtree_append_printf(tree, "}");
	
	unsigned free_list_id = function_queue_submit_free(shared->fqueue, list_type);
	stringtree_append_printf(tree, "func_%u(list);", free_list_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














