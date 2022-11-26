
#include <assert.h>

#include <debug.h>

/*#include <type/struct.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

/*#include <set/string/add.h>*/

/*#include <quack/append.h>*/

/*#include <type_cache/get_type/bool.h>*/

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_concat_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_list_concat);
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct list_concat_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* left = expression_print_source(this->left, shared, environment);
	
	struct stringtree* right = expression_print_source(this->right, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u* left = ", super->type->id);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "struct type_%u* right = ", super->type->id);
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* concat = func_%u();", super->type->id, new_id);
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "for (unsigned i = 0, n = left->n; i < n; i++)");
	stringtree_append_printf(tree, "	func_%u(concat, left->data[i]);", append_id);
	
	stringtree_append_printf(tree, "for (unsigned i = 0, n = right->n; i < n; i++)");
	stringtree_append_printf(tree, "	func_%u(concat, right->data[i]);", append_id);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(left);", free_id);
	stringtree_append_printf(tree, "func_%u(right);", free_id);
	
	stringtree_append_printf(tree, "concat;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
}































