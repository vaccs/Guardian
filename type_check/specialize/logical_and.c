
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <expression/struct.h>
#include <expression/logical_and/new.h>
#include <expression/free.h>

#include "inclusive_or.h"
#include "logical_and.h"

struct expression* specialize_logical_and_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_logical_and_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_inclusive_or_expression(tcache, sshared, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_logical_and_expression(tcache, sshared, scope, zexpression->left);
		
		struct expression* right = specialize_inclusive_or_expression(tcache, sshared, scope, zexpression->right);
		
		if (left->type->kind != tk_bool || right->type->kind != tk_bool)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal)
		{
			if (right->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				TODO;
			}
		}
		else
		{
			if (right->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				retval = new_logical_and_expression(tcache, left, right);
			}
		}
		
		free_expression(left), free_expression(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













