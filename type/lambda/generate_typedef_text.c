
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>

#include "struct.h"
#include "generate_typedef_text.h"

struct stringtree* lambda_type_generate_typedef_text(
	struct type* super,
	struct type_lookup* tlookup)
{
	ENTER;
	
	struct lambda_type* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	dpv(super->id);
	
	stringtree_append_printf(tree, ""
		"typedef struct {"
	"");
	
	TODO;
	#if 0
	type_lookup(tlookup, this->rettype);
	
	stringtree_append_printf(tree, ""
		"type_%u (*funcptr)("
	"", this->rettype->id);
	
	for (unsigned i = 0, n = this->parameters->n; i < n; i++)
	{
		struct parameter* p = this->parameters->data[i];
		
		type_lookup(tlookup, p->type);
		
		stringtree_append_printf(tree, "type_%u", p->type->id);
		
		if (i + 1 < n)
		{
			stringtree_append_printf(tree, ", ");
		}
	}
	
	stringtree_append_printf(tree, ""
			");"
		"} type_%u;"
	"", super->id);
	#endif
	
	EXIT;
	return tree;
}




















