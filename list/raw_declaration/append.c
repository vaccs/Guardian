
#include <debug.h>

#include <memory/srealloc.h>

#include <parse/declaration/inc.h>

#include "struct.h"
#include "append.h"

void raw_declaration_list_append(
	struct raw_declaration_list* this,
	struct raw_declaration* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_raw_declaration(element);
	
	EXIT;
}

