
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <type_cache/get_type/int.h>
#include <type_cache/get_type/lambda.h>
#include <type_cache/get_type/grammar.h>

#include "build_type.h"

static struct type* helper(
	struct type_cache* tcache,
	struct zebu_primary_type* type)
{
	if (type->int_type)
	{
		return type_cache_get_int_type(tcache);
	}
	else if (type->char_type)
	{
		TODO;
	}
	else if (type->float_type)
	{
		TODO;
	}
	else if (type->grammar)
	{
		struct string* tokenstring = new_string_from_token(type->grammar);
		
		dpvs(tokenstring);
		
		struct type* retval = type_cache_get_grammar_type(tcache, tokenstring);
		
		free_string(tokenstring);
		
		return retval;
	}
	else if (type->array)
	{
		TODO;
	}
	else if (type->tuple)
	{
		TODO;
	}
	else
	{
		TODO;
	}
}

struct type* build_type(
	struct type_cache* tcache,
	struct zebu_type* type)
{
	if (type->base)
	{
		return helper(tcache, type->base);
	}
	else if (type->lambda)
	{
		// '$' #lambda (type #args[] (',' type #args[])*)? ':' type #rettype
		
		struct type_list* tlist = new_type_list();
		
		for (unsigned i = 0, n = type->args.n; i < n; i++)
		{
			struct type* arg = build_type(tcache, type->args.data[i]);
			
			type_list_append(tlist, arg);
		}
		
		struct type* rettype = build_type(tcache, type->rettype);
		
		struct type* returnme = type_cache_get_lambda_type(tcache, tlist, rettype);
		
		free_type_list(tlist);
		
		return returnme;
	}
	else
	{
		TODO;
	}
}















