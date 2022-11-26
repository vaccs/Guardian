
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>
#include <expression/isaccessibleto_form/new.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

#include <expression/struct.h>

#include <defines/argv0.h>

#include <type/print.h>

#include <type_cache/get_string_type.h>
#include <type_cache/get_bool_type.h>

#include "../expression.h"

#include "isaccessibleto_form.h"

struct expression* specialize_primary_isaccessibleto_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len == 2);
	
	struct expression* path = specialize_expression(tcache, scope, raw_arguments[0]);
	
	struct expression* user = specialize_expression(tcache, scope, raw_arguments[1]);
	
	struct type* path_type = type_cache_get_string_type(tcache);
	
	if (path->type != path_type || user->type != path_type)
	{
		struct stringtree* tree = new_stringtree();
		
		stringtree_append_printf(tree, "%s: bad types for builtin isaccessibleto!(): '", argv0);
		
		{
			struct stringtree* subtree = type_print2(path->type);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
		}
		
		stringtree_append_printf(tree, "' and '");
		
		
		{
			struct stringtree* subtree = type_print2(user->type);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
		}
		
		stringtree_append_printf(tree, "'!\n");
		
		stringtree_stream(tree, stderr);
		
		exit(1);
	}
	
	struct type* type = type_cache_get_bool_type(tcache);
	
	retval = new_isaccessibleto_form_expression(type, path, user);
	
	free_expression(path);
	
	free_expression(user);
	
	EXIT;
	return retval;
}

