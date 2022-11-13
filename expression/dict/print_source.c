
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/struct.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>

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
	
/*	struct dict_type* dtype = (void*) type;*/
	
	type_queue_submit(shared->tqueue, type);
	
	stringtree_append_printf(tree, "({");
	
	struct expression_pair_list* elements = this->elements;
	
	stringtree_append_printf(tree,
		"struct type_%u_pair* elements = malloc(sizeof(*data) * %u);", type->id, elements->n);
	
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
	
	stringtree_append_printf(tree, "for (bool changed = true; changed; )");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	changed = false;");
	stringtree_append_printf(tree, "	for (unsigned i = 0, n = num_elements - 1; i < n; i++)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		struct value_pair* this = elements[i];");
	stringtree_append_printf(tree, "		struct value_pair* that = elements[i + 1];");
	stringtree_append_printf(tree, "		int cmp = compare_values(this->key, that->key);");
	stringtree_append_printf(tree, "		if (cmp > 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			elements->data[i] = that;");
	stringtree_append_printf(tree, "			elements->data[i + 1] = this;");
	stringtree_append_printf(tree, "			changed = true;");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "		else if (cmp == 0)");
	stringtree_append_printf(tree, "		{");
	stringtree_append_printf(tree, "			assert(!\"TODO\");");
	stringtree_append_printf(tree, "		}");
	stringtree_append_printf(tree, "	}");
	stringtree_append_printf(tree, "}");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(elements, num_elements);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














