
#include <debug.h>

#include <type/struct.h>

/*#include <value/print_source.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* bool_not_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct bool_not_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* subtree =
		expression_print_source(this->subexpression, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u* subvalue = ", super->type->id);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ";");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* value = func_%u(!subvalue->value);", super->type->id, new_id);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(subvalue);", free_id);
	
	stringtree_append_printf(tree, "value;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}

























