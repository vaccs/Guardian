
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/type_lookup/lookup.h>

#include "struct.h"
#include "generate_typedef_text.h"

struct stringtree* list_type_generate_typedef_text(
	struct type* super,
	struct type_lookup* tlookup)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct list_type* this = (void*) super;
	
	dpv(super->id);
	
	type_lookup(tlookup, this->element_type, super);
	
	stringtree_append_printf(tree, ""
		"typedef struct {"
			"type_%u** data;"
			"unsigned n, cap, refcount;"
		"} type_%u;"
	"", this->element_type->id, super->id);
	
	EXIT;
	return tree;
}

