
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <out/get_type_id.h>

#include <list/expression/struct.h>

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
	
	unsigned functype = out_get_type_id(shared, this->lambda->type);
	
	stringtree_append_printf(tree, "({\n");
	
	stringtree_append_printf(tree, "type_%u func = ", functype);
	stringtree_append_tree(tree, expression_print_source(this->lambda, shared));
	stringtree_append_printf(tree, ";");
	
	struct expression_list* arguments = this->arguments;
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		unsigned atid = out_get_type_id(shared, argument->type);
		
		stringtree_append_printf(tree, "type_%u arg_%u = ", atid, i);
		stringtree_append_tree(tree, expression_print_source(argument, shared));
		stringtree_append_printf(tree, ";");
	}
	
	unsigned rettype = out_get_type_id(shared, super->type);
	
	stringtree_append_printf(tree, "type_%u retval = func(", rettype);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		stringtree_append_printf(tree, "arg_%u", i);
		
		if (i + 1 < n)
			stringtree_append_printf(tree, ", ");
	}
	
	stringtree_append_printf(tree, ");");
	
	stringtree_append_printf(tree, "free_type_%u(func);", functype);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		unsigned atid = out_get_type_id(shared, argument->type);
		
		stringtree_append_printf(tree, "free_type_%u(arg_%u);", atid, i);
	}
	
	stringtree_append_printf(tree, "retval;");
	
	stringtree_append_printf(tree, "})\n");
	
	EXIT;
	return tree;
}














