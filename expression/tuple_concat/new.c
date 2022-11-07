
#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

/*#include <type/free.h>*/

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct expression* new_tuple_concat_expression(
	struct type* type,
	struct expression* left,
	struct expression* right)
{
	ENTER;
	
	struct tuple_concat_expression* this = (void*) new_expression(
		ek_tuple_concat,
		&tuple_concat_expression_inheritance,
		type,
		sizeof(struct tuple_concat_expression));
	
	this->left = inc_expression(left);
	this->right = inc_expression(right);
	
	EXIT;
	return (void*) this;
}









