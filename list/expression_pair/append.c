
#include <debug.h>

#include <memory/srealloc.h>

#include <pair/expression/inc.h>

#include "struct.h"
#include "append.h"

void expression_pair_list_append(
	struct expression_pair_list* this,
	struct expression_pair* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_expression_pair(element);
	
	EXIT;
}

