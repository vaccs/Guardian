
#include <debug.h>

#include <type_cache/get_type/bool.h>

#include <type/inc.h>
#include <type/free.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct expression* new_primitive_comparision_expression(
	struct type_cache *tcache,
	enum comparison_kind kind,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	assert(left->type == right->type);
	
	struct type* type = type_cache_get_bool_type(tcache);
	
	struct primitive_comparision_expression* this = (void*) new_expression(
		ek_primitive_comparision,
		&primitive_comparision_expression_inheritance,
		type,
		sizeof(struct primitive_comparision_expression));
	
	this->kind = kind;
	
	this->left = inc_expression(left);
	this->right = inc_expression(right);
	
	this->type = inc_type(left->type);
	
	free_type(type);
	
	EXIT;
	return (void*) this;
}









