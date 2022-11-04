
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <list/expression/struct.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_free.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_free.h>

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
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({\n");
	
	struct type* ltype = this->lambda->type;
	
	type_queue_submit(shared->tqueue, ltype);
	
	stringtree_append_printf(tree, "struct type_%u* function = ", ltype->id);
	struct stringtree* ltree = expression_print_source(this->lambda, shared);
	stringtree_append_tree(tree, ltree);
	stringtree_append_printf(tree, ";");
	
	struct expression_list* arguments = this->arguments;
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		type_queue_submit(shared->tqueue, argument->type);
		
		unsigned atid = argument->type->id;
		
		stringtree_append_printf(tree, "struct type_%u* arg_%u = ", atid, i);
		
		struct stringtree* atree = expression_print_source(argument, shared);
		
		stringtree_append_tree(tree, atree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(atree);
	}
	
	unsigned rid = super->type->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* retval = (function->evaluate)(function"
	"", rid);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		stringtree_append_printf(tree, ", arg_%u", i);
	}
	
	stringtree_append_printf(tree, ");");
	
	unsigned func_free_id = function_queue_submit_free(shared->fqueue, ltype);
	
	stringtree_append_printf(tree, "func_%u(function);", func_free_id);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct expression* argument = arguments->data[i];
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, argument->type);
		
		stringtree_append_printf(tree, "func_%u(arg_%u);", free_id, i);
	}
	
	stringtree_append_printf(tree, "retval;");
	
	stringtree_append_printf(tree, "})\n");
	
	free_stringtree(ltree);
	
	EXIT;
	return tree;
}














