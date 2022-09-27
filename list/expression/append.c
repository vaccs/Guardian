
#include <debug.h>

#include <expression/inc.h>

#include "struct.h"
#include "append.h"

void expression_list_append(
	struct expression_list* this,
	struct expression* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_expression(element);
	
	EXIT;
}

