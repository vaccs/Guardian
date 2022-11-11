
#include <stdlib.h>

#include <debug.h>

#include <stringtree/free.h>

#include <set/string/free.h>

#include <quack/free.h>

#include "struct.h"
#include "free.h"

void free_declare_queue(struct declare_queue* this)
{
	ENTER;
	
	free_quack(this->todo);
	
	free_stringset(this->queued);
	
	free_stringset(this->done);
	
	free_stringtree(this->text);
	
	free(this);
	
	EXIT;
}

