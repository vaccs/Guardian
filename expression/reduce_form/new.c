
#include <assert.h>
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_reduce_form_expression(
	struct type* type,
	struct expression* lambda,
	struct expression* list,
	struct expression* initial)
{
	ENTER;
	
	struct reduce_form_expression* this = (void*) new_expression(
		ek_reduce_form,
		&reduce_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->lambda = inc_expression(lambda);
	
	this->list = inc_expression(list);
	
	this->initial = inc_expression(initial);
	
	EXIT;
	return (void*) this;
}

