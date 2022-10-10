
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_typedef_text.h"

struct stringtree* grammar_type_generate_typedef_text(
	struct type* super,
	struct type_lookup* tlookup)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	dpv(super->id);
	
	stringtree_append_printf(tree, ""
		"typedef struct {"
			"unsigned refcount;"
		"} type_%u;"
	"", super->id);
	
	EXIT;
	return tree;
}

