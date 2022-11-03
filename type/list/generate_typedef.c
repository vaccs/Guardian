
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/type_queue/submit.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* list_type_generate_typedef(
	struct type* super,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct list_type* this = (void*) super;
	
	dpv(super->id);
	
	type_queue_submit(tqueue, this->element_type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u {"
			"struct type_%u** data;"
			"unsigned n, cap, refcount;"
		"};"
	"", super->id, this->element_type->id);
	
	EXIT;
	return tree;
}

