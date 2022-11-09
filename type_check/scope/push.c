
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "node/compare.h"
#include "node/free.h"

#include "layer.h"
#include "struct.h"
#include "push.h"

void type_check_scope_push(
	struct type_check_scope* this)
{
	ENTER;
	
	struct type_check_scope_layer* new = smalloc(sizeof(*new));
	
	new->tree = avl_alloc_tree(
		compare_type_check_scope_nodes,
		free_type_check_scope_node);
	
	new->is_pure = true;
	
	new->prev = this->head;
	this->head = new;
	
	EXIT;
}

