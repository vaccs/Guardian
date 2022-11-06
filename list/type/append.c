
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "append.h"

void type_list_append(
	struct type_list* this,
	struct type* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = element;
	
	EXIT;
}

