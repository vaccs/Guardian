
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
	
	struct int_math_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	unsigned tid = super->type->id;
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u();"
	"", tid, new_id);
	
	switch (this->kind)
	{
		case imek_negate:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"mpz_neg(result->value, left->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left);", free_id);
			
			free_stringtree(left);
			break;
		}
		
		case imek_add:
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
				"mpz_add(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_subtract:
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
				"mpz_sub(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_multiply:
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
				"mpz_mul(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_qdivide:
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
				"mpz_fdiv_q(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_rdivide:
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
				"mpz_fdiv_r(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_expo:
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
				"if (mpz_fits_ulong_p(right->value))"
				"{"
					"unsigned long right_ulong = mpz_get_ui(right->value);"
					"mpz_pow_ui(result->value, left->value, right_ulong);"
				"}"
				"else if (mpz_cmp_ui(right->value, 0) < 0)"
				"{"
					"assert(!\"TODO: negative expo\");"
				"}"
				"else"
				"{"
					"assert(!\"TODO\");"
				"}"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_bitnot:
		{
			struct stringtree* left = expression_print_source(this->left, shared, environment);
			
			stringtree_append_printf(tree, "struct type_%u *left = ", tid);
			stringtree_append_tree(tree, left);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"mpz_com(result->value, left->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left);", free_id);
			
			free_stringtree(left);
			break;
		}
		
		case imek_bitand:
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
				"mpz_and(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_bitior:
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
				"mpz_ior(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_bitxor:
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
				"mpz_xor(result->value, left->value, right->value);"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_lshift:
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
				"if (mpz_fits_ulong_p(right->value))"
				"{"
					"unsigned long right_ulong = mpz_get_ui(right->value);"
					"mpz_mul_2exp(result->value, left->value, right_ulong);"
				"}"
				"else if (mpz_cmp_ui(right->value, 0) < 0)"
				"{"
					"if (mpz_fits_slong_p(right->value))"
					"{"
						"signed long right_slong = mpz_get_si(right->value);"
						"mpz_fdiv_q_2exp(result->value, left->value, -right_slong);"
					"}"
					"else"
					"{"
						"assert(!\"TODO in lshift\");"
					"}"
				"}"
				"else"
				"{"
					"assert(!\"TODO\");"
				"}"
			"");
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
			
			stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_rshift:
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
				"if (mpz_fits_ulong_p(right->value))"
				"{"
					"unsigned long right_ulong = mpz_get_ui(right->value);"
					"mpz_fdiv_q_2exp(result->value, left->value, right_ulong);"
				"}"
				"else if (mpz_cmp_ui(right->value, 0) < 0)"
				"{"
					"if (mpz_fits_slong_p(right->value))"
					"{"
						"signed long right_slong = mpz_get_si(right->value);"
						"mpz_mul_2exp(result->value, left->value, -right_slong);"
					"}"
					"else"
					"{"
						"assert(!\"TODO in lshift\");"
					"}"
				"}"
				"else"
				"{"
					"assert(!\"TODO\");"
				"}"
			"");
			
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














