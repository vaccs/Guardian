
#include <assert.h>

#include <debug.h>

#include <type/set/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

/*#include <type/struct.h>*/
/*#include <type/set_init/struct.h>*/

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_compare.h>
/*#include <out/function_queue/submit_append.h>*/
#include <out/function_queue/submit_free.h>

#include <list/expression/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* set_init_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct set_init_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	type_queue_submit(shared->tqueue, type);
	
	struct set_type* stype = (void*) type;
	
	stringtree_append_printf(tree, "({");
	
	struct expression_list* elements = this->elements;
	
	unsigned etid = stype->element_type->id;
	
	stringtree_append_printf(tree,
		"struct type_%u** elements = malloc(sizeof(*elements) * %u);", etid, elements->n);
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		struct stringtree* subtree = expression_print_source(elements->data[i], shared, environment);
		
		stringtree_append_printf(tree, "elements[%u] = ", i);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(subtree);
	}
	
	stringtree_append_printf(tree, "unsigned num_elements = %u;", elements->n);
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, stype->element_type);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, stype->element_type);
	
	stringtree_append_printf(tree, "for (bool changed = true; changed; )");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	changed = false;");
	stringtree_append_printf(tree, "	");
	stringtree_append_printf(tree, "	for (unsigned i = 0, n = num_elements - 1; i < n; i++)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		struct type_%u *this = elements[i], *that = elements[i + 1];", etid);
	stringtree_append_printf(tree, "		");
	stringtree_append_printf(tree, "		int cmp = func_%u(this, that);", compare_id);
	stringtree_append_printf(tree, "		");
	stringtree_append_printf(tree, "		if (cmp > 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			elements[i] = that;");
	stringtree_append_printf(tree, "			elements[i + 1] = this;");
	stringtree_append_printf(tree, "			changed = true;");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "		else if (cmp == 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			func_%u(this);", free_id);
	stringtree_append_printf(tree, "			memmove(elements + i, elements + i + 1, sizeof(*elements) * (n - i));");
	stringtree_append_printf(tree, "			num_elements--, n--;");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "	}");
	stringtree_append_printf(tree, "}");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(elements, num_elements);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}
























