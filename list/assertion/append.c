
#include <debug.h>

#include <memory/srealloc.h>

#include <assertion/inc.h>

#include "struct.h"
#include "append.h"

void assertion_list_append(
	struct assertion_list* this,
	struct assertion* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_assertion(element);
	
	EXIT;
}

