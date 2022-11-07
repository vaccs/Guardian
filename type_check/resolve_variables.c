
#include <string.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <type/free.h>

#include "unresolved/foreach.h"
#include "unresolved/new.h"
#include "unresolved/inc.h"
#include "unresolved/add.h"
#include "unresolved/resolve.h"
#include "unresolved/update.h"
#include "unresolved/discard.h"
#include "unresolved/free.h"
#include "unresolved/encase.h"

#include "build_type.h"
#include "resolve_variables.h"

static void resolve_variables_primary(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression);
	
	if (expression->integer_literal)
	{
		;
	}
	else if (expression->float_literal)
	{
		;
	}
	else if (expression->character_literal)
	{
		;
	}
	else if (expression->string_literal)
	{
		;
	}
	else if (expression->true_literal)
	{
		;
	}
	else if (expression->false_literal)
	{
		;
	}
	else if (expression->identifier)
	{
		struct string* name = new_string_from_token(expression->identifier);
		
		dpvs(name);
		
		unresolved_add(unresolved, name, expression);
		
		free_string(name);
	}
	else if (false
		|| expression->len_form
		|| expression->float_form)
	{
		resolve_variables(unresolved, tcache, expression->arg);
	}
	#if 0
	else if (expression->map)
	{
		for (unsigned i = 0, n = expression->args.n; i < n; i++)
		{
			resolve_variables(unresolved, tcache, expression->args.data[i]);
		}
	}
	#endif
	else if (expression->paren)
	{
		if (expression->tuple)
		{
			for (unsigned i = 0, n = expression->elements.n; i < n; i++)
			{
				resolve_variables(unresolved, tcache, expression->elements.data[i]);
			}
		}
		else
		{
			resolve_variables(unresolved, tcache, expression->subexpression);
		}
	}
	else if (expression->list)
	{
		for (unsigned i = 0, n = expression->elements.n; i < n; i++)
		{
			resolve_variables(unresolved, tcache, expression->elements.data[i]);
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_postfix(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_postfix_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_primary(unresolved, tcache, expression->base);
	}
	else if (expression->sub)
	{
		resolve_variables_postfix(unresolved, tcache, expression->sub);
		
		if (expression->index)
		{
			resolve_variables(unresolved, tcache, expression->index);
		}
		else if (expression->field)
		{
			;
		}
		else if (expression->tupleindex)
		{
			;
		}
		else if (expression->call)
		{
			for (unsigned i = 0, n = expression->args.n; i < n; i++)
			{
				resolve_variables(unresolved, tcache, expression->args.data[i]);
			}
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

static void resolve_variables_unary(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_unary_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_postfix(unresolved, tcache, expression->base);
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

static void resolve_variables_exponentiation(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_exponentiation_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_unary(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		assert(expression->right);
		
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_multiplicative(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_multiplicative_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_exponentiation(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		assert(expression->right);
		
		resolve_variables_multiplicative(unresolved, tcache, expression->left);
		
		resolve_variables_exponentiation(unresolved, tcache, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_additive(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_additive_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_multiplicative(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		assert(expression->right);
		
		resolve_variables_additive(unresolved, tcache, expression->left);
		
		resolve_variables_multiplicative(unresolved, tcache, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_shift(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_shift_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_additive(unresolved, tcache, expression->base);
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

static void resolve_variables_relational(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_relational_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_shift(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		resolve_variables_relational(unresolved, tcache, expression->left);
		resolve_variables_shift(unresolved, tcache, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_equality(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_equality_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_relational(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		assert(expression->right);
		
		resolve_variables_equality(unresolved, tcache, expression->left);
		
		resolve_variables_relational(unresolved, tcache, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_and(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_and_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_equality(unresolved, tcache, expression->base);
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

static void resolve_variables_exclusive_or(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_exclusive_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_and(unresolved, tcache, expression->base);
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

static void resolve_variables_inclusive_or(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_inclusive_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_exclusive_or(unresolved, tcache, expression->base);
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

static void resolve_variables_logical_and(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_logical_and_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_inclusive_or(unresolved, tcache, expression->base);
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

static void resolve_variables_logical_or(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_logical_or_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_logical_and(unresolved, tcache, expression->base);
	}
	else if (expression->left)
	{
		resolve_variables_logical_or(unresolved, tcache, expression->left);
		
		resolve_variables_logical_and(unresolved, tcache, expression->right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_inclusion(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_inclusion_expression* expression)
{
	ENTER;
	
	resolve_variables_logical_or(unresolved, tcache, expression->base);
	
	if (expression->list)
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_possession(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_possession_expression* expression)
{
	ENTER;
	
	resolve_variables_inclusion(unresolved, tcache, expression->base);
	
	EXIT;
}

static void resolve_variables_implication(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_implication_expression* expression)
{
	ENTER;
	
	resolve_variables_possession(unresolved, tcache, expression->base);
	
	if (expression->implies)
	{
		TODO;
	}
	
	EXIT;
}

static void resolve_variables_conditional(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_conditional_expression* expression)
{
	ENTER;
	
	resolve_variables_implication(unresolved, tcache, expression->base);
	
	if (expression->true_case)
	{
		resolve_variables(unresolved, tcache, expression->true_case);
		resolve_variables_conditional(unresolved, tcache, expression->false_case);
	}
	
	EXIT;
}

static void resolve_variables_lambda(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_lambda_expression* expression)
{
	ENTER;
	
	if (expression->base)
	{
		resolve_variables_conditional(unresolved, tcache, expression->base);
	}
	else if (expression->lambda)
	{
		struct unresolved* subunresolved = new_unresolved();
		
		resolve_variables_lambda(subunresolved, tcache, expression->lambda);
		
		// remove parameters
		if (expression->name)
		{
			struct type* type = build_type(tcache, expression->type);
			
			struct string* name = new_string_from_token(expression->name);
			
			unresolved_resolve_type(subunresolved, name, vek_parameter, type);
			
			unresolved_discard(subunresolved, name);
			
			for (unsigned i = 0, n = expression->parameters.n; i < n; i++)
			{
				struct zebu_0$parameter* parameter = expression->parameters.data[i];
				
				if (parameter->type)
				{
					struct type* new_type = build_type(tcache, expression->type);
					
					type = new_type;
				}
				
				struct string* name = new_string_from_token(parameter->name);
				
				unresolved_resolve_type(subunresolved, name, vek_parameter, type);
				
				unresolved_discard(subunresolved, name);
				
				free_string(name);
			}
			
			free_string(name);
		}
		
		struct unresolved* lambda_captures = new_unresolved();
		
		// fill out `lambda_captures`:
		unresolved_foreach(subunresolved, ({
			void runme(struct string* name)
			{
				struct zebu_primary_expression* expression = smalloc(sizeof(*expression));
				memset(expression, 0, sizeof(*expression));
				expression->refcount = 1;
				unresolved_add(lambda_captures, name, expression);
				free_zebu_primary_expression(expression);
			}
			runme;
		}));
		
		expression->lambda_captures = lambda_captures;
		
		unresolved_update(unresolved, lambda_captures);
		
		unresolved_encase(subunresolved);
		unresolved_update(unresolved, subunresolved);
		
		free_unresolved(subunresolved);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

void resolve_variables(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_expression* expression)
{
	ENTER;
	
	resolve_variables_lambda(unresolved, tcache, expression->base);
	
	EXIT;
}























