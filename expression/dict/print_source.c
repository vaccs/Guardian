
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/struct.h>

#include <type/struct.h>
#include <type/dict/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_compare.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct dict_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	struct dict_type* dtype = (void*) type;
	
	type_queue_submit(shared->tqueue, type);
	
	stringtree_append_printf(tree, "({");
	
	struct expression_pair_list* elements = this->elements;
	
	stringtree_append_printf(tree,
		"struct type_%u_pair* elements = malloc(sizeof(*elements) * %u);", type->id, elements->n);
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		struct expression_pair* element = elements->data[i];
		
		struct stringtree* key = expression_print_source(element->key, shared, environment);
		
		stringtree_append_printf(tree, "elements[%u].key = ", i);
		stringtree_append_tree(tree, key);
		stringtree_append_printf(tree, ";");
		
		struct stringtree* value = expression_print_source(element->value, shared, environment);
		
		stringtree_append_printf(tree, "elements[%u].value = ", i);
		stringtree_append_tree(tree, value);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(key);
		free_stringtree(value);
	}
	
	stringtree_append_printf(tree, "unsigned num_elements = %u;", elements->n);
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, dtype->key);
	
	stringtree_append_printf(tree, "for (bool changed = true; changed; )");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	changed = false;");
	stringtree_append_printf(tree, "	for (unsigned i = 0, n = num_elements - 1; i < n; i++)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		int cmp = func_%u(elements[i].key, elements[i + 1].key);", compare_id);
	stringtree_append_printf(tree, "		if (cmp > 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			struct type_%u_pair temp = elements[i + 1];", type->id);
	stringtree_append_printf(tree, "			elements[i + 1] = elements[i];");
	stringtree_append_printf(tree, "			elements[i] = temp;");
	stringtree_append_printf(tree, "			changed = true;");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "		else if (cmp == 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			assert(!\"TODO: dict expression\");");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "	}");
	stringtree_append_printf(tree, "}");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(elements, num_elements);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














