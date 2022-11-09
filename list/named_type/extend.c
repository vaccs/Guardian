
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "extend.h"

void named_type_list_extend(
	struct named_type_list* this,
	const struct named_type_list* other)
{
	ENTER;
	
	while (this->n + other->n > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	for (unsigned i = 0, n = other->n; i < n; i++)
	{
		TODO;
/*		this->data[this->n++] = other->data[i];*/
	}
	
	EXIT;
}

