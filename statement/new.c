
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct statement* new_statement(
	unsigned line,
	enum statement_kind kind,
	struct statement_inheritance* inheritance,
	unsigned alloc_size)
{
	ENTER;
	
	dpv(line);
	
	struct statement* this = smalloc(alloc_size);
	
	this->kind = kind;
	
	this->line = line;
	
	this->inheritance = inheritance;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

