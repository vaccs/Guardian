
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_string_concat_expression(
	struct type* type,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct string_concat_expression* this = (void*) new_expression(
		ek_string_concat,
		&string_concat_expression_inheritance,
		type,
		sizeof(struct string_concat_expression));
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















