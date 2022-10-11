
#include <debug.h>

/*#include <yacc/structinfo/print_source.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* grammar_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup)
{
	ENTER;
	
	TODO;
	#if 0
	struct grammar_type* this = (void*) super;
	
	struct stringtree* tree = structinfo_print_source(this->structinfo, super->id);
	
	EXIT;
	return tree;
	#endif
}

