
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct statement* new_statement(
	enum statement_kind kind,
	struct statement_inheritance* inheritance,
	unsigned alloc_size)
{
	ENTER;
	
	struct statement* this = smalloc(alloc_size);
	
	this->kind = kind;
	
	this->inheritance = inheritance;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

