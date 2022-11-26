
#include <assert.h>
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_filter_form_expression(
	struct type* type,
	struct expression* lambda,
	struct expression* list)
{
	ENTER;
	
	struct filter_form_expression* this = (void*) new_expression(
		ek_filter_form,
		&filter_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->lambda = inc_expression(lambda);
	
	this->list = inc_expression(list);
	
	EXIT;
	return (void*) this;
}

