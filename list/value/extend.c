
#include <debug.h>

#include <memory/srealloc.h>

#include <value/inc.h>

#include "struct.h"
#include "extend.h"

void value_list_extend(
	struct value_list* this,
	const struct value_list* other)
{
	ENTER;
	
	while (this->n + other->n > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	for (unsigned i = 0, n = other->n; i < n; i++)
	{
		this->data[this->n++] = inc_value(other->data[i]);
	}
	
	EXIT;
}

