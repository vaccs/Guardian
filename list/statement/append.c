
#include <debug.h>

#include <memory/srealloc.h>

#include <statement/inc.h>

#include "struct.h"
#include "append.h"

void statement_list_append(
	struct statement_list* this,
	struct statement* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_statement(element);
	
	EXIT;
}

