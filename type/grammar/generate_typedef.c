
#include <assert.h>

#include <debug.h>

/*#include <yacc/structinfo/print_source.h>*/

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>

#include <out/type_queue/submit.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* grammar_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct grammar_type* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"struct type_%u {"
	"", super->id);
	
	for (unsigned i = 0, n = this->fields->n; i < n; i++)
	{
		struct parameter* p = this->fields->data[i];
		
		type_queue_submit(tlookup, p->type);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* $%.*s; "
		"", p->type->id, p->name->len, p->name->chars);
	}
	
	stringtree_append_printf(tree, ""
			"unsigned refcount;"
		"};"
	"");
	
	EXIT;
	return tree;
}





















