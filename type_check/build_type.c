
#include <debug.h>

#include <parse/parse.h>

#include <type_cache/get_type/int.h>

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
		TODO;
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
	else if (type->rettype)
	{
		TODO;
	}
	else
	{
		TODO;
	}
}















