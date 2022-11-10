
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "layer.h"
#include "pop.h"

void type_check_scope_pop(
	struct type_check_scope* this)
{
	ENTER;
	
	assert(this->head);
	
	struct type_check_scope_layer* old = this->head;
	
	avl_free_tree(old->tree);
	
	this->head = old->prev;
	
	free(old);
	
	EXIT;
}

