
#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>
#include <type/print.h>

#include <expression/struct.h>
#include <expression/free.h>
#include <expression/print.h>

#include <expression/ternary/new.h>

#include "expression.h"
#include "logical_or.h"
#include "conditional.h"

struct expression* specialize_conditional_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_conditional_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->qmark)
	{
		TODO;
		#if 0
		struct expression* conditional = specialize_logical_or_expression(tcache, zexpression->base);
		
		if (conditional->type->kind != tk_bool)
		{
			TODO;
			exit(1);
		}
		
		struct expression* true_case = specialize_expression(tcache, zexpression->true_case);
		
		struct expression* false_case = specialize_conditional_expression(tcache, zexpression->false_case);
		
		if (true_case->type != false_case->type)
		{
			fprintf(stderr, "maia: incompatiable data types in true and false case of "
				"ternary: \n\t(");
			
			type_print(true_case->type);
			printf(") ");
			expression_print(true_case), printf(" and \n\t(");
			type_print(false_case->type);
			printf(") ");
			expression_print(false_case), puts(".");
			
			exit(1);
		}
		
		retval = new_ternary_expression(true_case->type, conditional, true_case, false_case);
		
		free_expression(conditional);
		free_expression(true_case);
		free_expression(false_case);
		#endif
	}
	else
	{
		retval = specialize_logical_or_expression(tcache, sshared, zexpression->base);
	}
	
	EXIT;
	return retval;
}













