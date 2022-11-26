
#include <assert.h>

#include <debug.h>

/*#include <yacc/structinfo/print_source.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>

#include <named/type/struct.h>

#include <list/named_type/foreach.h>

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
	
	named_type_list_foreach(this->fields, ({
		void runme(struct named_type* field)
		{
			type_queue_submit(tlookup, field->type);
			
			stringtree_append_printf(tree, "struct type_%u* $", field->type->id);
			
			stringtree_append_string(tree, field->name);
			
			stringtree_append_printf(tree, ";");
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
			"unsigned refcount;"
		"};"
	"");
	
	EXIT;
	return tree;
}





















