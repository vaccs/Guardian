
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

struct stringtree* float_math_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_float_math);
	
	struct stringtree* tree = new_stringtree();
	
	struct float_math_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	unsigned tid = super->type->id;
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	switch (this->kind)
	{
		case fmek_negate:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(-left->value);"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left);", free_id);
			
			free_stringtree(left);
			break;
		}
		
		case fmek_add:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(left->value + right->value);"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case fmek_subtract:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(left->value - right->value);"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case fmek_multiply:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(left->value * right->value);"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case fmek_qdivide:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(left->value / right->value);"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case fmek_rdivide:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(fmodq(left->value, right->value));"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case fmek_expo:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			struct stringtree* right = expression_print_source(this->right, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, "struct type_%u *right = ", tid);
			stringtree_append_tree(tree, right);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* result = func_%u(powq(left->value, right->value));"
			"", tid, new_id);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	
	EXIT;
	return tree;
}










	#if 0
	assert(super->kind == ek_float_math);
	
	struct stringtree* tree = new_stringtree();
	
	struct float_math_expression* this = (void*) super;
	
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
		"struct type_%u* result = func_%u("
	"", tid, new_id);
	
	switch (this->kind)
	{
		case fmek_add:
			stringtree_append_printf(tree, ""
				"left->value + right->value"
			"");
			break;
		
		case fmek_subtract:
			stringtree_append_printf(tree, ""
				"left->value - right->value"
			"");
			break;
		
		default:
		{
			dpv(this->kind);
			
			TODO;
			break;
		}
	}
	
	stringtree_append_printf(tree, ""
		");"
	"");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
	#endif




