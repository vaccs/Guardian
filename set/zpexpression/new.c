
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

static void item_free(void* a)
{
	free_zebu_primary_expression(a);
}

struct zpexpressionset* new_zpexpressionset()
{
	ENTER;
	
	struct zpexpressionset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, item_free);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

