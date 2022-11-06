
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct zebu_expression_list* new_zebu_expression_list()
{
	ENTER;
	
	struct zebu_expression_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

