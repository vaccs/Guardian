
#include <assert.h>

#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_list_slice_expression(
	struct type* type,
	struct expression* list,
	struct expression* startindex,
	struct expression* endindex)
{
	ENTER;
	
	assert(startindex || endindex);
	
	struct list_slice_expression* this = (void*) new_expression(
		ek_list_slice,
		&list_slice_expression_inheritance,
		type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	this->startindex = inc_expression(startindex);
	
	this->endindex = inc_expression(endindex);
	
	EXIT;
	return (void*) this;
}

