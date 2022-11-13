
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_set_math_expression(
	struct type* type,
	enum set_math_expression_kind kind,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct set_math_expression* this = (void*) new_expression(
		ek_set_math,
		&set_math_expression_inheritance,
		type,
		sizeof(struct set_math_expression));
	
	this->kind = kind;
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















