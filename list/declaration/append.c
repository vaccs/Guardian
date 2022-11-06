
#include <debug.h>

#include <memory/srealloc.h>

#include <declaration/inc.h>

#include "struct.h"
#include "append.h"

void declaration_list_append(
	struct declaration_list* this,
	struct declaration* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_declaration(element);
	
	EXIT;
}

