
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <out/shared.h>*/
/*#include <out/type_lookup/lookup.h>*/
#include <out/type_queue/submit.h>

#include <list/type/struct.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* tuple_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct tuple_type* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"struct type_%u"
		"{"
	"", super->id);
	
	for (unsigned i = 0, n = this->subtypes->n; i < n; i++)
	{
		struct type* type = this->subtypes->data[i];
		
		type_queue_submit(tlookup, type);
		
		stringtree_append_printf(tree, "struct type_%u* $%u;", type->id, i);
	}
	
	stringtree_append_printf(tree, ""
			"unsigned refcount;"
		"};"
	"");
	
	EXIT;
	return tree;
}




















