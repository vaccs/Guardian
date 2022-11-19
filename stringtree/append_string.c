
#include <memory/smalloc.h>

#include <debug.h>

#include <string/inc.h>

#include "struct.h"
#include "append_string.h"

void stringtree_append_string(
	struct stringtree* this,
	struct string* string)
{
	ENTER;
	
	struct stringtree_node* node = smalloc(sizeof(*node));
	
	node->kind = snk_string;
	node->string = inc_string(string);
	node->next = NULL;
	
	if (this->tail)
	{
		this->tail->next = node;
		this->tail = node;
	}
	else
	{
		this->head = this->tail = node;
	}
	
	EXIT;
}















