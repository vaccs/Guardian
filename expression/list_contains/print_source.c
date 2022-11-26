
#include <assert.h>

#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_compare.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_contains_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_list_contains);
	
	struct list_contains_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* element = expression_print_source(this->element, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* element = ", this->element->type->id);
	stringtree_append_tree(tree, element);
	stringtree_append_printf(tree, ";");
	
	struct stringtree* list = expression_print_source(this->list, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* list = ", this->list->type->id);
	stringtree_append_tree(tree, list);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "bool found = false;");
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, this->element->type);
	
	stringtree_append_printf(tree, "for (unsigned i = 0, n = list->n; !found && i < n; i++)");
	stringtree_append_printf(tree, "	if (!func_%u(element, list->data[i]))", compare_id);
	stringtree_append_printf(tree, "		found = true;");
	
	unsigned free_id1 = function_queue_submit_free(shared->fqueue, this->element->type);
	unsigned free_id2 = function_queue_submit_free(shared->fqueue, this->list->type);
	
	stringtree_append_printf(tree, "func_%u(element);", free_id1);
	stringtree_append_printf(tree, "func_%u(list);", free_id2);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(found);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(element);
	free_stringtree(list);
	
	EXIT;
	return tree;
}














