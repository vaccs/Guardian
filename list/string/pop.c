
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "pop.h"

void string_list_pop(
	struct string_list* this)
{
	assert(this->n);
	
	this->n--;
}

