
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

struct stringtree* all_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct all_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* subtree = expression_print_source(this->list, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u* list = ", this->list->type->id);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "bool all = true;");
	
	stringtree_append_printf(tree, "for (unsigned i = 0, n = list->n; all && i < n; i++)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	all = list->data[i]->value;");
	stringtree_append_printf(tree, "}");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* result = func_%u(all);", super->type->id, new_id);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->list->type);
	
	stringtree_append_printf(tree, "func_%u(list);", free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}














