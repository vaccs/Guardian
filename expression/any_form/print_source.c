
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

struct stringtree* any_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct any_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* subtree = expression_print_source(this->list, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u* list = ", this->list->type->id);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "bool any = false;");
	
	stringtree_append_printf(tree, "for (unsigned i = 0, n = list->n; !any && i < n; i++)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	any = list->data[i]->value;");
	stringtree_append_printf(tree, "}");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* result = func_%u(any);", super->type->id, new_id);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->list->type);
	
	stringtree_append_printf(tree, "func_%u(list);", free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}














