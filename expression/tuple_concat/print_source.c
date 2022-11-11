
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>
/*#include <type/print_source.h>*/
#include <type/tuple/struct.h>

#include <list/type/struct.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* tuple_concat_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	struct tuple_concat_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	type_queue_submit(shared->tqueue, this->left->type);
	
	type_queue_submit(shared->tqueue, this->right->type);
	
	unsigned rid = super->type->id;
	
	unsigned left_id = this->left->type->id;
	
	unsigned right_id = this->right->type->id;
	
	struct stringtree* left_tree = expression_print_source(this->left, shared);
	
	struct stringtree* right_tree = expression_print_source(this->right, shared);
	
	stringtree_append_printf(tree, "struct type_%u *left = ", left_id);
	stringtree_append_tree(tree, left_tree);
	stringtree_append_printf(tree, ";\n");
	
	stringtree_append_printf(tree, "struct type_%u *right = ", right_id);
	stringtree_append_tree(tree, right_tree);
	stringtree_append_printf(tree, ";\n");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u("
	"", rid, new_id);
	
	struct tuple_type* left_type = (void*) this->left->type;
	
	bool first = true;
	
	for (unsigned i = 0, n = left_type->subtypes->n; i < n; i++)
	{
		if (first)
			first = false;
		else
			stringtree_append_printf(tree, ", ");
		
		stringtree_append_printf(tree, "left->$%u", i);
	}

	struct tuple_type* right_type = (void*) this->right->type;
	
	for (unsigned i = 0, n = right_type->subtypes->n; i < n; i++)
	{
		if (first)
			first = false;
		else
			stringtree_append_printf(tree, ", ");
		
		stringtree_append_printf(tree, "right->$%u", i);
	}
	
	stringtree_append_printf(tree, ""
			");"
	"");
	
	unsigned left_free_id = function_queue_submit_free(shared->fqueue, this->left->type);
	
	unsigned right_free_id = function_queue_submit_free(shared->fqueue, this->right->type);
	
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", left_free_id, right_free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left_tree), free_stringtree(right_tree);
	
	EXIT;
	return tree;
	#endif
}














