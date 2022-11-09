
#include <debug.h>

#include <memory/srealloc.h>

#include <named/type/inc.h>

#include "struct.h"
#include "append.h"

void named_type_list_append(
	struct named_type_list* this,
	struct named_type* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_named_type(element);
	
	EXIT;
}

