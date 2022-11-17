
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct statement* inc_statement(
	struct statement* statement)
{
	ENTER;
	
	if (statement)
	{
		statement->refcount++;
	}
	
	EXIT;
	return statement;
}

