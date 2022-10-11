
#include <debug.h>

#include <expression/inc.h>

#include <type/free.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_ternary_expression(
	struct type* type,
	struct expression* conditional,
	struct expression* true_case,
	struct expression* false_case)
{
	ENTER;
	
	struct ternary_expression* this = (void*) new_expression(
		ek_ternary,
		&ternary_expression_inheritance,
		type,
		sizeof(*this));
	
	this->conditional = inc_expression(conditional);
	
	this->true_case = inc_expression(true_case);
	
	this->false_case = inc_expression(false_case);
	
	EXIT;
	return (void*) this;
}

