
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/type_queue/submit.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* dict_type_generate_typedef(
	struct type* super,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct dict_type* this = (void*) super;
	
	dpv(super->id);
	
	type_queue_submit(tqueue, this->key);
	type_queue_submit(tqueue, this->value);
	
	stringtree_append_printf(tree, ""
		"struct type_%u {"
			"struct type_%u_pair { "
				"struct type_%u* key;"
				"struct type_%u* value;"
			"}* data;"
			"unsigned n, refcount;"
		"};"
	"", super->id, super->id, this->key->id, this->value->id);
	
	EXIT;
	return tree;
}



















