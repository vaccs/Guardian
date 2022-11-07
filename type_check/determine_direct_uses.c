
#include <assert.h>
#include <stdbool.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <set/string/add.h>

#include <parse/parse.h>

#include "determine_direct_uses.h"

static void determine_direct_uses_primary(
	struct stringset* direct_uses,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	if (false
		|| expression->integer_literal
		|| expression->float_literal
		|| expression->character_literal
		|| expression->string_literal
		|| expression->true_literal
		|| expression->false_literal)
	{
		;
	}
	else if (expression->identifier)
	{
		struct string* string = new_string_from_token(expression->identifier);
		
		stringset_add(direct_uses, string);
		
		free_string(string);
	}
	else if (false
		|| expression->len_form)
	{
		TODO;
	}
	#if 0
	else if (false
		|| expression->all_form
	{
		TODO;
	}
	#endif
	else if (expression->paren)
	{
		if (expression->tuple)
		{
			for (unsigned i = 0, n = expression->elements.n; i < n; i++)
			{
				determine_direct_uses(direct_uses, expression->elements.data[i]);
			}
		}
		else
		{
			determine_direct_uses(direct_uses, expression->elements.data[0]);
		}
	}
	else if (expression->list)
	{
		if (expression->emptytype)
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
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_postfix(
	struct stringset* direct_uses,
	struct zebu_postfix_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_primary(direct_uses, expression->base);
	}
	else if (expression->sub)
	{
		if (expression->index)
		{
			determine_direct_uses_postfix(direct_uses, expression->sub);
			determine_direct_uses(direct_uses, expression->index);
		}
		else if (expression->field)
		{
			determine_direct_uses_postfix(direct_uses, expression->sub);
		}
		else if (expression->call)
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
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_unary(
	struct stringset* direct_uses,
	struct zebu_unary_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_postfix(direct_uses, expression->base);
	}
	else if (expression->sub)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_exponentiation(
	struct stringset* direct_uses,
	struct zebu_exponentiation_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_unary(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_multiplicative(
	struct stringset* direct_uses,
	struct zebu_multiplicative_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_exponentiation(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_additive(
	struct stringset* direct_uses,
	struct zebu_additive_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_multiplicative(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		determine_direct_uses_additive(direct_uses, expression->left);
		determine_direct_uses_multiplicative(direct_uses, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_shift(
	struct stringset* direct_uses,
	struct zebu_shift_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_additive(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_relational(
	struct stringset* direct_uses,
	struct zebu_relational_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_shift(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_equality(
	struct stringset* direct_uses,
	struct zebu_equality_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_relational(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	EXIT;
}

static void determine_direct_uses_and(
	struct stringset* direct_uses,
	struct zebu_and_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_equality(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_exclusive_or(
	struct stringset* direct_uses,
	struct zebu_exclusive_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_and(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_inclusive_or(
	struct stringset* direct_uses,
	struct zebu_inclusive_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_exclusive_or(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	
	EXIT;
}

static void determine_direct_uses_logical_and(
	struct stringset* direct_uses,
	struct zebu_logical_and_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_inclusive_or(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_logical_or(
	struct stringset* direct_uses,
	struct zebu_logical_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_logical_and(direct_uses, expression->base);
	}
	else if (expression->left)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_inclusion(
	struct stringset* direct_uses,
	struct zebu_inclusion_expression* expression)
{
	ENTER;
	
	determine_direct_uses_logical_or(direct_uses, expression->base);
		
	if (expression->list)
	{
		determine_direct_uses_logical_or(direct_uses, expression->list);
	}
	
	EXIT;
}


static void determine_direct_uses_possession(
	struct stringset* direct_uses,
	struct zebu_possession_expression* expression)
{
	ENTER;
	
	determine_direct_uses_inclusion(direct_uses, expression->base);
	
	EXIT;
}

static void determine_direct_uses_implies(
	struct stringset* direct_uses,
	struct zebu_implication_expression* expression)
{
	ENTER;
	
	determine_direct_uses_possession(direct_uses, expression->base);
	
	if (expression->implies)
	{
		determine_direct_uses_implies(direct_uses, expression->implies);
	}
	
	EXIT;
}

static void determine_direct_uses_conditional(
	struct stringset* direct_uses,
	struct zebu_conditional_expression* expression)
{
	ENTER;
	
	determine_direct_uses_implies(direct_uses, expression->base);
	
	if (expression->qmark)
	{
		TODO;
	}
	
	EXIT;
}

static void determine_direct_uses_lambda(
	struct stringset* direct_uses,
	struct zebu_lambda_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		determine_direct_uses_conditional(direct_uses, expression->base);
	}
	else if (expression->lambda)
	{
		;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

void determine_direct_uses(
	struct stringset* direct_uses,
	struct zebu_expression* expression)
{
	ENTER;
	
	determine_direct_uses_lambda(direct_uses, expression->base);
	
	EXIT;
}















