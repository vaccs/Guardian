
#include <stdlib.h>

#include <debug.h>

#include <set/string/free.h>

#include <stringtree/free.h>

#include <quack/free.h>

#include "struct.h"
#include "free.h"

void free_set_queue(struct set_queue* this)
{
	ENTER;
	
	free_quack(this->todo);
	
	free_stringset(this->queued);
	
	free_stringtree(this->init_text);
	
	free_stringtree(this->assign_text);
	
	free_stringtree(this->uninit_text);
	
	free(this);
	
	EXIT;
}

