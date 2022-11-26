
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

#include <type/struct.h>
#include <type/dict/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_compare.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_math_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_dict_math);
	
	struct stringtree* tree = new_stringtree();
	
	struct dict_math_expression* this = (void*) super;
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct dict_type* dtype = (void*) super->type;
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* left = expression_print_source(this->left, shared, environment);
	struct stringtree* right = expression_print_source(this->right, shared, environment);
	
	unsigned tid = super->type->id;
	
	stringtree_append_printf(tree, "struct type_%u* left = ", tid);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "struct type_%u* right = ", tid);
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "unsigned i = 0, j = 0, n = left->n, m = right->n, un = 0;");
	
	unsigned compare_key_id = function_queue_submit_compare(shared->fqueue, dtype->key);
	
	unsigned inc_key_id = function_queue_submit_inc(shared->fqueue, dtype->key);
	unsigned inc_val_id = function_queue_submit_inc(shared->fqueue, dtype->key);
	
	switch (this->kind)
	{
		case dmek_union:
		{
			stringtree_append_printf(tree, "struct type_%u_pair* new = malloc(sizeof(*new) * (n + m));", tid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i], *re = &right->data[j];", tid);
			
			stringtree_append_printf(tree, "	int cmp = func_%u(le->key, re->key);", compare_key_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, i++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, i++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i];", tid);
			stringtree_append_printf(tree, "	new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "	new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "	un++, i++;");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *re = &right->data[j];", tid);
			stringtree_append_printf(tree, "	new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "	new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "	un++, j++;");
			stringtree_append_printf(tree, "}");
			break;
		}
		
		case dmek_intersect:
		{
			stringtree_append_printf(tree, "struct type_%u_pair* new = malloc(sizeof(*new) * (n + m));", tid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i], *re = &right->data[j];", tid);
			
			stringtree_append_printf(tree, "	int cmp = func_%u(le->key, re->key);", compare_key_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		i++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, i++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "}");
			break;
		}
		
		case dmek_symdifference:
		{
			stringtree_append_printf(tree, "struct type_%u_pair* new = malloc(sizeof(*new) * (n + m));", tid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i], *re = &right->data[j];", tid);
			
			stringtree_append_printf(tree, "	int cmp = func_%u(le->key, re->key);", compare_key_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, i++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		i++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i];", tid);
			stringtree_append_printf(tree, "	new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "	new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "	un++, i++;");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *re = &right->data[j];", tid);
			stringtree_append_printf(tree, "	new[un].key   = func_%u(re->key);", inc_key_id);
			stringtree_append_printf(tree, "	new[un].value = func_%u(re->value);", inc_val_id);
			stringtree_append_printf(tree, "	un++, j++;");
			stringtree_append_printf(tree, "}");
			break;
		}
		
		case dmek_difference:
		{
			stringtree_append_printf(tree, "struct type_%u_pair* new = malloc(sizeof(*new) * (n + m));", tid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i], *re = &right->data[j];", tid);
			
			stringtree_append_printf(tree, "	int cmp = func_%u(le->key, re->key);", compare_key_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "		new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "		un++, i++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "	{");
			stringtree_append_printf(tree, "		i++, j++;");
			stringtree_append_printf(tree, "	}");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	struct type_%u_pair *le = &left->data[i];", tid);
			stringtree_append_printf(tree, "	new[un].key   = func_%u(le->key);", inc_key_id);
			stringtree_append_printf(tree, "	new[un].value = func_%u(le->value);", inc_val_id);
			stringtree_append_printf(tree, "	un++, i++;");
			stringtree_append_printf(tree, "}");
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(new, un);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
}



































