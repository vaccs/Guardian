
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_declare_queue(struct declare_queue* this)
{
	free_quack(this->todo);
	
	free_stringset(this->queued);
	
	free_stringtree(this->init_text);
	free_stringtree(this->uninit_text);
	
	free(this);
}

