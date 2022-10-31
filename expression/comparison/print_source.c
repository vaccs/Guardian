
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

/*#include <type/print_source.h>*/

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_new.h>*/
/*#include <out/function_lookup/lookup_compare.h>*/
/*#include <out/function_lookup/lookup_free.h>*/
#include <out/type_queue/submit.h>

#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_compare.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

static const char* lookup[] = {
	[cek_equal_to] = "==",
};

struct stringtree* comparison_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct comparison_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	type_queue_submit(shared->tqueue, this->type);
	
	unsigned rid = super->type->id;
	unsigned tid = this->type->id;
	
	struct stringtree* left = expression_print_source(this->left, shared);
	
	struct stringtree* right = expression_print_source(this->right, shared);
	
	stringtree_append_printf(tree, "type_%u *_left = ", tid);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ", *_right = ");
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";\n");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, this->type);
	
	stringtree_append_printf(tree, ""
		"type_%u* _cmp = func_%u(func_%u(_left, _right) %s 0);"
	"", rid, new_id, compare_id, lookup[this->kind]);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->type);
	
	stringtree_append_printf(tree, "func_%u(_left), func_%u(_right);", free_id, free_id);
	
	stringtree_append_printf(tree, "_cmp;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
}














