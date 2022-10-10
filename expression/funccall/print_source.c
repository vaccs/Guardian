
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <list/expression/struct.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* funccall_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct funccall_expression* this = (void*) super;
	
	type_lookup(shared->tlookup, this->lambda->type);
	
	stringtree_append_printf(tree, "({\n");
	
	stringtree_append_printf(tree, "type_%u* func = ", this->lambda->type->id);
	stringtree_append_tree(tree, expression_print_source(this->lambda, shared));
	stringtree_append_printf(tree, ";");
	
	struct expression_list* arguments = this->arguments;
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		type_lookup(shared->tlookup, argument->type);
		
		unsigned atid = argument->type->id;
		
		stringtree_append_printf(tree, "type_%u* arg_%u = ", atid, i);
		stringtree_append_tree(tree, expression_print_source(argument, shared));
		stringtree_append_printf(tree, ";");
	}
	
	type_lookup(shared->tlookup, super->type);
	
	unsigned return_id = super->type->id;
	
	stringtree_append_printf(tree, "type_%u* retval = func(", return_id);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		stringtree_append_printf(tree, "arg_%u", i);
		
		if (i + 1 < n)
			stringtree_append_printf(tree, ", ");
	}
	
	stringtree_append_printf(tree, ");");
	
	unsigned func_free_id = function_lookup_free(shared->flookup, this->lambda->type);
	
	stringtree_append_printf(tree, "func_%u(func);", func_free_id);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		unsigned free_id = function_lookup_free(shared->flookup, argument->type);
		
		stringtree_append_printf(tree, "func_%u(arg_%u);", free_id, i);
	}
	
	stringtree_append_printf(tree, "retval;");
	
	stringtree_append_printf(tree, "})\n");
	
	EXIT;
	return tree;
}














