
#include <assert.h>
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct expression* new_comparison_expression(
	struct type* type,
	enum comparison_expression_kind kind,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	assert(left->type == right->type);
	
	struct comparison_expression* this = (void*) new_expression(
		ek_comparison,
		&comparison_expression_inheritance,
		type,
		sizeof(struct comparison_expression));
	
	this->kind = kind;
	
	this->left = inc_expression(left);
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}









