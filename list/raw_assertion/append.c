
#include <debug.h>

#include <memory/srealloc.h>

#include <parse/assertion/inc.h>

#include "struct.h"
#include "append.h"

void raw_assertion_list_append(
	struct raw_assertion_list* this,
	struct raw_assertion* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_raw_assertion(element);
	
	EXIT;
}

