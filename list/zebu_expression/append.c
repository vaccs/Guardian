
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "append.h"

void zebu_expression_list_append(
	struct zebu_expression_list* this,
	struct zebu_expression* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_zebu_expression(element);
	
	EXIT;
}

