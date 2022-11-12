
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_dict_math_expression(
	struct type* type,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct dict_math_expression* this = (void*) new_expression(
		ek_dict_math,
		&dict_math_expression_inheritance,
		type,
		sizeof(struct dict_math_expression));
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















