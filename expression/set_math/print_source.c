
#include <assert.h>

#include <debug.h>

/*#include <type/struct.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_compare.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>
#include <type/set/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* set_math_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_set_math);
	
	struct stringtree* tree = new_stringtree();
	
	struct set_math_expression* this = (void*) super;
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct set_type* stype = (void*) super->type;
	
	stringtree_append_printf(tree, "({");
	
	unsigned tid = super->type->id;
	unsigned eid = stype->element_type->id;
	
	struct stringtree* left = expression_print_source(this->left, shared, environment);
	
	struct stringtree* right = expression_print_source(this->right, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u* left = ", tid);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "struct type_%u* right = ", tid);
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "unsigned i = 0, j = 0, n = left->n, m = right->n, un = 0;");
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, stype->element_type);
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, stype->element_type);
	
	switch (this->kind)
	{
		case smek_union:
		{
			stringtree_append_printf(tree, "struct type_%u** new = malloc(sizeof(*new) * (n + m));", eid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	int cmp = func_%u(left->data[i], right->data[j]);", compare_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "		new[un++] = func_%u(left->data[i++]);", inc_id);
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "		new[un++] = func_%u(right->data[j++]);", inc_id);
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "		new[un++] = func_%u(right->data[i++, j++]);", inc_id);
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n) new[un++] = func_%u(left->data[i++]);", inc_id);
			
			stringtree_append_printf(tree, "while (j < m) new[un++] = func_%u(right->data[j++]);", inc_id);
			break;
		}
		
		case smek_intersect:
		{
			stringtree_append_printf(tree, "struct type_%u** new = malloc(sizeof(*new) * (MIN(n, m)));", eid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	int cmp = func_%u(left->data[i], right->data[j]);", compare_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "		i++;");
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "		j++;");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "		new[un++] = func_%u(right->data[i++, j++]);", inc_id);
			stringtree_append_printf(tree, "}");
			break;
		}
		
		case smek_symdifference:
		{
			stringtree_append_printf(tree, "struct type_%u** new = malloc(sizeof(*new) * (n + m));", eid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	int cmp = func_%u(left->data[i], right->data[j]);", compare_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "		new[un++] = func_%u(left->data[i++]);", inc_id);
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "		new[un++] = func_%u(right->data[j++]);", inc_id);
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "		i++, j++;");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n) new[un++] = func_%u(left->data[i++]);", inc_id);
			
			stringtree_append_printf(tree, "while (j < m) new[un++] = func_%u(right->data[j++]);", inc_id);
			break;
		}
		
		case smek_difference:
		{
			stringtree_append_printf(tree, "struct type_%u** new = malloc(sizeof(*new) * n);", eid);
			
			stringtree_append_printf(tree, "while (i < n && j < m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	int cmp = func_%u(left->data[i], right->data[j]);", compare_id);
			
			stringtree_append_printf(tree, "	if (cmp < 0)");
			stringtree_append_printf(tree, "		new[un++] = func_%u(left->data[i++]);", inc_id);
			stringtree_append_printf(tree, "	else if (cmp > 0)");
			stringtree_append_printf(tree, "		j++;");
			stringtree_append_printf(tree, "	else");
			stringtree_append_printf(tree, "		i++, j++;");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "while (i < n) new[un++] = func_%u(left->data[i++]);", inc_id);
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



































