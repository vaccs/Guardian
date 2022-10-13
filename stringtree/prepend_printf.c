
#include <debug.h>

#include "struct.h"
#include "prepend_printf.h"

void stringtree_prepend_printf(
	struct stringtree* this,
	const char* fmt, ...)
{
	ENTER;
	
	char* string;
	
	va_list ap;
	va_start(ap, fmt);

	if (vasprintf(&string, fmt, ap) < 0)
	{
		TODO;
		exit(1);
	}
	
	va_end(ap);
	
	dpvs(string);
	
	struct stringtree_node* node = smalloc(sizeof(*node));
	
	node->is_branch = false;
	node->string = string;
	node->next = NULL;
	
	if (this->head)
	{
		node->next = this->head;
		this->head = node;
	}
	else
	{
		this->head = this->tail = node;
	}
	
	EXIT;
}















