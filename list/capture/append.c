
#include <assert.h>

#include <debug.h>

#include <memory/srealloc.h>

#include <capture/inc.h>

#include "struct.h"
#include "append.h"

void capture_list_append(
	struct capture_list* this,
	struct capture* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_capture(element);
	
	EXIT;
}

