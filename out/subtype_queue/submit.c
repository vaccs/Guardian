
#include <debug.h>

#include <quack/append.h>

#include <set/ptr/add.h>

#include "struct.h"
#include "submit.h"

void subtype_queue_submit_value(
	struct subtype_queue* this,
	struct lambda_value* value)
{
	ENTER;
	
	if (ptrset_add(this->values.queued, value))
		quack_append(this->values.todo, value);
	
	EXIT;
}

void subtype_queue_submit_expression(
	struct subtype_queue* this,
	struct lambda_expression* lexpression)
{
	ENTER;
	
	if (ptrset_add(this->expressions.queued, lexpression))
		quack_append(this->expressions.todo, lexpression);
	
	EXIT;
}

