
#include <debug.h>

#include <memory/srealloc.h>

#include <parse/raw_statement/inc.h>

#include "struct.h"
#include "append.h"

void raw_statement_list_append(
	struct raw_statement_list* this,
	struct raw_statement* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_raw_statement(element);
	
	EXIT;
}

