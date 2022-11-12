
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct expression* new_float_math_expression(
	struct type* type,
	enum float_math_expression_kind kind,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	assert(left);
	
	struct float_math_expression* this = (void*) new_expression(
		ek_float_math,
		&float_math_expression_inheritance,
		type,
		sizeof(struct float_math_expression));
	
	this->kind = kind;
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}









