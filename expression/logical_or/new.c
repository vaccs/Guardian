
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_logical_or_expression(
	struct type* type,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct logical_or_expression* this = (void*) new_expression(
		ek_logical_or,
		&logical_or_expression_inheritance,
		type,
		sizeof(struct logical_or_expression));
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















