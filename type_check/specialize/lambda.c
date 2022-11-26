

/*#include <named/type/new.h>*/
/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

/*#include <type/free.h>*/

/*#include <value/lambda/new.h>*/
/*#include <value/free.h>*/

/*#include <list/type/free.h>*/

/*#include <type/print.h>*/

/*#include <list/parameter/is_nonempty.h>*/
/*#include <list/parameter/free.h>*/

/*#include <capture/new.h>*/
/*#include <capture/free.h>*/

/*#include <list/capture/new.h>*/
/*#include <list/capture/append.h>*/
/*#include <list/capture/is_nonempty.h>*/
/*#include <list/capture/free.h>*/

/*#include <expression/struct.h>	*/
/*#include <expression/lambda/new.h>*/
/*#include <expression/literal/new.h>*/
/*#include <expression/free.h>*/

/*#include "../unresolved/foreach.h"*/
/*#include "../unresolved/is_nonempty.h"*/

/*#include "shared.h"*/

#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <parse/parse.h>

#include <string/new.h>
#include <string/free.h>

/*#include <parameter/new.h>*/

#include <list/named_type/new.h>
#include <list/named_type/append.h>
#include <list/named_type/free.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

/*#include <parameter/free.h>*/

/*#include <type_cache/get_type/environment.h>*/
#include <type_cache/get_lambda_type.h>

#include <type/print.h>

#include <named/type/new.h>
#include <named/type/free.h>

#include <expression/struct.h>
#include <expression/lambda/new.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include <value/lambda/new.h>
#include <value/free.h>

#include "conditional.h"
#include "let.h"
#include "lambda.h"

#include "../scope/layer.h"
#include "../scope/struct.h"
#include "../scope/is_head_pure.h"
#include "../scope/declare.h"
#include "../scope/push.h"
#include "../scope/pop.h"

#include "../build_type.h"

struct expression* specialize_lambda_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_lambda_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_conditional_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->lambda)
	{
		struct type_list* types = new_type_list();
		
		struct named_type_list* named_types = new_named_type_list();
		
		type_check_scope_push(scope);
		
		if (zexpression->name)
		{
			struct type* type = build_primitive_type(tcache, zexpression->type);
			
			struct string* name = new_string_from_token(zexpression->name);
			
			struct named_type* named_type = new_named_type(name, type);
			
			type_list_append(types, type);
			
			named_type_list_append(named_types, named_type);
			
			type_check_scope_declare(scope, name, type);
			
			free_named_type(named_type);
			
			free_string(name);
			
			for (unsigned i = 0, n = zexpression->parameters.n; i < n; i++)
			{
				struct zebu_1$parameter* raw_named_type = zexpression->parameters.data[i];
				
				if (raw_named_type->type)
				{
					struct type* new = build_primitive_type(tcache, raw_named_type->type);
					
					type = new;
				}
				
				struct string* name = new_string_from_token(raw_named_type->name);
				
				struct named_type* named_type = new_named_type(name, type);
				
				type_list_append(types, type);
				
				named_type_list_append(named_types, named_type);
				
				type_check_scope_declare(scope, name, type);
				
				free_named_type(named_type);
				
				free_string(name);
			}
		}
		
		struct expression* body = specialize_let_expression(tcache, scope, zexpression->lambda);
		
		struct type* rettype = build_type(tcache, zexpression->rettype);
		
		struct type* type = type_cache_get_lambda_type(tcache, types, rettype);
		
		if (rettype != body->type)
		{
			struct stringtree* tree = new_stringtree();
			
			stringtree_append_printf(tree, ""
				"%s: incompatiable types: lambda return type does not match "
					"type returned by lambda body!\n"
			"", argv0);
			
			{
				stringtree_append_printf(tree, ""
					"%s: lambda return type: "
				"", argv0);
				
				struct stringtree* sub = type_print2(rettype);
				
				stringtree_append_tree(tree, sub);
				
				stringtree_append_printf(tree, "\n");
				
				free_stringtree(sub);
			}
			
			{
				stringtree_append_printf(tree, ""
					"%s: lambda body type: "
				"", argv0);
				
				struct stringtree* sub = type_print2(body->type);
				
				stringtree_append_tree(tree, sub);
				
				stringtree_append_printf(tree, "\n");
				
				free_stringtree(sub);
			}
			
			stringtree_stream(tree, stderr);
			
			free_stringtree(tree);
			exit(1);
		}
		
		if (type_check_scope_is_head_pure(scope))
		{
			struct value* new = new_lambda_value(type, named_types, NULL, body);
			
			retval = new_literal_expression(new);
			
			free_value(new);
		}
		else
		{
			retval = new_lambda_expression(type, named_types, body);
		}
		
		free_type_list(types);
		
		free_named_type_list(named_types);
		
		free_expression(body);
		
		type_check_scope_pop(scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













