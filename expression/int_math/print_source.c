
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>
/*#include <type/print_source.h>*/

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* int_math_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_int_math);
	
	struct stringtree* tree = new_stringtree();
	
/*	struct dict_concat_expression* this = (void*) super;*/
	
	stringtree_append_printf(tree, "({"
		"assert(!\"TODO: int-math\");"
		"NULL;"
	"})");
	
	#if 0
	struct stringtree* tree = new_stringtree();
	
	struct int_math_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	unsigned tid = super->type->id;
	
	struct stringtree* left = expression_print_source(this->left, shared);
	
	struct stringtree* right = expression_print_source(this->right, shared);
	
	stringtree_append_printf(tree, "struct type_%u *left = ", tid);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ", *right = ");
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";\n");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u();"
	"", tid, new_id);
	
	switch (this->kind)
	{
		case imek_add:
			stringtree_append_printf(tree, ""
				"mpz_add(result->value, left->value, right->value);"
			"");
			break;
		
		case imek_subtract:
			stringtree_append_printf(tree, ""
				"mpz_sub(result->value, left->value, right->value);"
			"");
			break;
		
		default:
		{
			dpv(this->kind);
			
			TODO;
			break;
		}
	}
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	#endif
	
	EXIT;
	return tree;
}














