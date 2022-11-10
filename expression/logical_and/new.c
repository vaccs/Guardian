
#include <assert.h>

#include <debug.h>

#include <type_cache/get_type/bool.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_logical_and_expression(
	struct type_cache* tcache,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct logical_and_expression* this = (void*) new_expression(
		ek_logical_and,
		&logical_and_expression_inheritance,
		type_cache_get_bool_type(tcache),
		sizeof(struct logical_and_expression));
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















