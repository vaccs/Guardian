
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

/*#include <string/free.h>*/

/*#include <expression/free.h>*/

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_statement(
	struct statement* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		assert(this->inheritance);
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
	
	EXIT;
}

