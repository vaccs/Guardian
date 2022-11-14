
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* len_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct len_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"({"
			"struct type_%u* list = "
	"", this->list->type->id);
	
	struct stringtree* subtree = expression_print_source(this->list, shared, environment);
	
	stringtree_append_tree(tree, subtree);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->list->type);
	
	stringtree_append_printf(tree, ""
			";"
			"struct type_%u* len = func_%u();"
			"mpz_set_ui(len->value, list->n);"
			"func_%u(list);"
			"len;"
		"})"
	"", super->type->id, new_id, free_id);
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}














