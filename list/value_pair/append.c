
#include <debug.h>

#include <memory/srealloc.h>

#include <pair/value/inc.h>

#include "struct.h"
#include "append.h"

void value_pair_list_append(
	struct value_pair_list* this,
	struct value_pair* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_value_pair(element);
	
	EXIT;
}

