
#include <string.h>
#include <stdio.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "append_strndup.h"

void stringtree_append_strndup(
	struct stringtree* this,
	const char* chars, unsigned length)
{
	ENTER;
	
	struct stringtree_node* node = smalloc(sizeof(*node));
	
	node->kind = snk_cstring;
	node->cstring = strndup(chars, length);
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















