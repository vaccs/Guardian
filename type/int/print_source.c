
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* int_type_print_source(
	struct type* super,
	struct type_lookup* tlookup)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	dpv(super->id);
	
	stringtree_append_printf(tree, ""
		"typedef struct {"
			"mpz_t value;"
			"unsigned refcount;"
		"} type_%u;"
	"", super->id);
	
	EXIT;
	return tree;
}

