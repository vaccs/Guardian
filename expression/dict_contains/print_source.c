
#include <assert.h>

#include <debug.h>

#include <type/struct.h>
#include <type/dict/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/function_queue/submit_compare.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_contains_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct dict_contains_expression* this = (void*) super;
	
	struct dict_type* dtype = (void*) this->dict->type;
	
	unsigned tid = super->type->id;
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* dict = expression_print_source(this->dict, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* dict = ", tid);
	stringtree_append_tree(tree, dict);
	stringtree_append_printf(tree, ";");
	
	struct stringtree* key = expression_print_source(this->element, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* key = ", tid);
	stringtree_append_tree(tree, key);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "	signed l = 0, r = dict->n - 1;");
	
	stringtree_append_printf(tree, "	bool found = false;");
	
	stringtree_append_printf(tree, "	while (!found && r >= l)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		int mid = l + (r - l) / 2;");
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, dtype->key);
	stringtree_append_printf(tree, "		int cmp = func_%u(dict->data[mid]->key, key);", compare_id);
	
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
	
	free_stringtree(dict), free_stringtree(key);
	
	EXIT;
	return tree;
}














