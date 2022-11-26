
#include <debug.h>

/*#include <memory/srealloc.h>*/

/*#include <parameter/inc.h>*/

#include "struct.h"
#include "append.h"

void parameter_list_append(
	struct parameter_list* this,
	struct parameter* element)
{
	ENTER;
	
	TODO;
	#if 0
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_parameter(element);
	#endif
	
	EXIT;
}

