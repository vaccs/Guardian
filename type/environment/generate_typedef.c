
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <avl/foreach.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <named/type/struct.h>

#include <out/type_queue/submit.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* environment_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup)
{
	ENTER;
	
	assert(super->kind == tk_environment);
	
	struct environment_type* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	dpv(super->id);
	
	stringtree_append_printf(tree, ""
		"struct type_%u"
		"{"
	"", super->id);
	
	avl_foreach(this->variables, ({
		void runme(void* ptr)
		{
			struct named_type* ntype = ptr;
			
			type_queue_submit(tlookup, ntype->type);
			
			stringtree_append_printf(tree, ""
				"struct type_%u* $%.*s;"
			"", ntype->type->id, ntype->name->len, ntype->name->chars);
		}
		runme;
	}));
	
	if (this->prev)
	{
		stringtree_append_printf(tree, "struct type_%u* prev; ", this->prev->super.id);
	}
	
	stringtree_append_printf(tree, ""
			"unsigned refcount;"
		"};"
	"");
	
	EXIT;
	return tree;
}















