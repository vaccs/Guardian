
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <parse/parse.h>

#include <type/struct.h>
#include <type/print.h>

#include <value/bool/struct.h>

#include <expression/literal/struct.h>
#include <expression/struct.h>
#include <expression/free.h>
#include <expression/print.h>
#include <expression/inc.h>

#include <expression/ternary/new.h>

#include "expression.h"
#include "implication.h"
#include "conditional.h"

struct expression* specialize_conditional_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_conditional_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->qmark)
	{
		struct expression* conditional = specialize_implication_expression(tcache, scope, zexpression->base);
		
		if (conditional->type->kind != tk_bool)
		{
			TODO;
			exit(1);
		}
		
		struct expression* true_case = specialize_expression(tcache, scope, zexpression->true_case);
		
		struct expression* false_case = specialize_conditional_expression(tcache, scope, zexpression->false_case);
		
		if (true_case->type != false_case->type)
		{
			fflush(stdout), puts("");
			
			fprintf(stderr, ""
				"%s: incompatiable data types in true and false case of ternary:"
				"\n\t("
			"", argv0);
			
			type_print(true_case->type);
			printf(") ");
			expression_print(true_case), printf(" and \n\t(");
			type_print(false_case->type);
			printf(") ");
			expression_print(false_case), puts(".");
			
			exit(1);
		}
		
		if (conditional->kind == ek_literal)
		{
			struct literal_expression* condlit = (void*) conditional;
			
			struct bool_value* condbool = (void*) condlit->value;
			
			if (condbool->value)
				retval = inc_expression(true_case);
			else
				retval = inc_expression(false_case);
		}
		else
		{
			retval = new_ternary_expression(true_case->type, conditional, true_case, false_case);
		}
		
		free_expression(conditional);
		free_expression(true_case);
		free_expression(false_case);
	}
	else
	{
		retval = specialize_implication_expression(tcache, scope, zexpression->base);
	}
	
	EXIT;
	return retval;
}













