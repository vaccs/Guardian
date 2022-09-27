
#include <debug.h>

#include <type_cache/get_type/int.h>

#include <type/free.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct expression* new_int_math_expression(
	struct type_cache *tcache,
	enum int_math_expression_kind kind,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct type* type = type_cache_get_int_type(tcache);
	
	struct int_math_expression* this = (void*) new_expression(
		ek_int_math,
		&int_math_expression_inheritance,
		type,
		sizeof(struct int_math_expression));
	
	this->kind = kind;
	
	this->left = inc_expression(left);
	this->right = inc_expression(right);
	
	free_type(type);
	
	EXIT;
	return (void*) this;
}









