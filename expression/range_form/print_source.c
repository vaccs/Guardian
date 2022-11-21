
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* range_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_range_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct range_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	if (this->start)
	{
		TODO;
	}
	else
	{
		stringtree_append_printf(tree, "unsigned native_start = 0;");
	}
	
	{
		struct stringtree* subtree = expression_print_source(this->end, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* end = ", this->end->type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		stringtree_append_printf(tree, ""
			"unsigned native_end;"
			""
			"if (mpz_fits_uint_p(end->value))"
			"{"
				"native_end = mpz_get_ui(end->value);"
			"}"
			"else"
			"{"
				"assert(!\"range!(): end bound too high or to low!\");"
			"}"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->end->type);
		stringtree_append_printf(tree, "func_%u(end);", free_id);
		
		free_stringtree(subtree);
	}
	
	unsigned list_new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* result = func_%u();", super->type->id, list_new_id);
	
	stringtree_append_printf(tree, "for (unsigned i = native_start; i < native_end; i++)");
	
	stringtree_append_printf(tree, "{");
	
	unsigned element_new_id = function_queue_submit_new(shared->fqueue, this->end->type);
	stringtree_append_printf(tree, "struct type_%u* element = func_%u();", this->end->type->id, element_new_id);
	
	stringtree_append_printf(tree, "mpz_set_si(element->value, i);");
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(result, element);", append_id);
	
	unsigned free_id = function_queue_submit_new(shared->fqueue, this->end->type);
	stringtree_append_printf(tree, "func_%u(element);", free_id);
	
	stringtree_append_printf(tree, "}");
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














