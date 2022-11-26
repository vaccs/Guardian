
#include <assert.h>

#include <stdlib.h>
#include <stdbool.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <type/lambda/struct.h>

#include <list/type/struct.h>

#include <type/list/struct.h>

#include <expression/literal/struct.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <defines/argv0.h>

#include <type/print.h>

#include <stringtree/stream.h>
#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/reduce_form/new.h>
#include <expression/reduce_form/run.h>

#include <expression/free.h>

#include "../expression.h"

#include "map_form.h"

struct expression* specialize_primary_reduce_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len == 3);
	
	struct expression* lambda_exp  = specialize_expression(tcache, scope, raw_arguments[0]);
	
	struct expression* list_exp    = specialize_expression(tcache, scope, raw_arguments[1]);
	
	struct expression* initial_exp = specialize_expression(tcache, scope, raw_arguments[2]);
	
	bool all_literals = true
		&&  lambda_exp->kind == ek_literal
		&&    list_exp->kind == ek_literal
		&& initial_exp->kind == ek_literal;
	
	if (lambda_exp->type->kind != tk_lambda || list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct lambda_type* ftype = (void*) lambda_exp->type;
	
	struct list_type* ltype = (void*) list_exp->type;
	
	if (false
		|| ftype->rettype != initial_exp->type
		|| ftype->parameters->n != 2
		|| ftype->parameters->data[0] != initial_exp->type
		|| ftype->parameters->data[1] != ltype->element_type)
	{
		struct stringtree* tree = new_stringtree();
		
		stringtree_append_printf(tree,
			"%s: bad types for invocation to reduce!() builtin: '", argv0);
		
		{
			struct stringtree* subtree = type_print2(lambda_exp->type);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
		
		}
		stringtree_append_printf(tree, "' and '");
		
		{
			struct stringtree* subtree = type_print2(list_exp->type);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
		}
		
		stringtree_append_printf(tree, "' and '");
		
		{
			struct stringtree* subtree = type_print2(initial_exp->type);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
		}
		
		stringtree_append_printf(tree, "'\n");
		
		stringtree_stream(tree, stderr);
		
		free_stringtree(tree);
		
		exit(1);
	}
	
	if (all_literals)
	{
		struct literal_expression* fe = (void*) lambda_exp;
		
		struct lambda_value* lambda = (void*) fe->value;
		
		struct literal_expression* le = (void*) list_exp;
		
		struct list_value* list = (void*) le->value;
		
		struct literal_expression* ie = (void*) initial_exp;
		
		struct value* initial = (void*) ie->value;
		
		struct value* result = reduce_form_run(tcache, list_exp->type, lambda, list, initial);
		
		retval = new_literal_expression(result);
		
		free_value(result);
	}
	else
	{
		retval = new_reduce_form_expression(initial_exp->type, lambda_exp, list_exp, initial_exp);
	}
	
	free_expression(lambda_exp);
	
	free_expression(list_exp);
	
	free_expression(initial_exp);
	
	EXIT;
	return retval;
}








