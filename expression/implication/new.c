
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_implication_expression(
	struct type* type,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct implication_expression* this = (void*) new_expression(
		ek_implication,
		&implication_expression_inheritance,
		type,
		sizeof(struct implication_expression));
	
	this->left = inc_expression(left);
	
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}





















