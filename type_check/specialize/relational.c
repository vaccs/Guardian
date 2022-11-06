
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <expression/struct.h>
#include <expression/comparison/new.h>
#include <expression/free.h>

#include "shift.h"
#include "relational.h"

struct expression* specialize_relational_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_relational_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_shift_expression(tcache, sshared, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_relational_expression(tcache, sshared, zexpression->left);
		
		struct expression* right = specialize_shift_expression(tcache, sshared, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			TODO;
		}
		else
		{
			if (zexpression->lt)
				retval = new_comparison_expression(tcache, cek_less_than, left, right);
			else if (zexpression->gt)
				retval = new_comparison_expression(tcache, cek_greater_than, left, right);
			else if (zexpression->lte)
			{
				TODO;
			}
			else if (zexpression->gte)
			{
				TODO;
			}
			else
			{
				TODO;
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



















