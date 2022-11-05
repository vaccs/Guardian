
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include <parse/parse.h>

#include "struct.h"
#include "add.h"

bool zpexpressionset_add(
	struct zpexpressionset* set,
	struct zebu_primary_expression* element)
{
	ENTER;
	
	bool new;
	struct avl_node_t* node = avl_insert(set->tree, element);
	
	if (node)
	{
		inc_zebu_primary_expression(element);
		new = true;
	}
	else if (errno == EEXIST)
	{
		new = false;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return new;
}

