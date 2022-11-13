
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/print_source.h>

#include <type/struct.h>
#include <type/set/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_compare.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* set_contains_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct set_contains_expression* this = (void*) super;
	
	struct set_type* stype = (void*) this->set->type;
	
	unsigned tid = super->type->id;
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* set = expression_print_source(this->set, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* set = ", tid);
	stringtree_append_tree(tree, set);
	stringtree_append_printf(tree, ";");
	
	struct stringtree* ele = expression_print_source(this->element, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* ele = ", tid);
	stringtree_append_tree(tree, ele);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "	signed l = 0, r = set->n - 1;");
	
	stringtree_append_printf(tree, "	bool found = false;");
	
	stringtree_append_printf(tree, "	while (!found && r >= l)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		int mid = l + (r - l) / 2;");
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, stype->element_type);
	stringtree_append_printf(tree, "		int cmp = func_%u(set->data[mid], ele);", compare_id);
	
	stringtree_append_printf(tree, "		if (cmp > 0)");
	stringtree_append_printf(tree, "			r = mid - 1;");
	stringtree_append_printf(tree, "		else if (cmp < 0)");
	stringtree_append_printf(tree, "			l = mid + 1;");
	stringtree_append_printf(tree, "		else");
	stringtree_append_printf(tree, "			found = true;");
	stringtree_append_printf(tree, "	}");
	
	unsigned new_id = function_queue_submit_compare(shared->fqueue, super->type);
	stringtree_append_printf(tree, "	func_%u(value);", new_id);
	stringtree_append_printf(tree, "})");
	
	free_stringtree(set), free_stringtree(ele);
	
	EXIT;
	return tree;
}














