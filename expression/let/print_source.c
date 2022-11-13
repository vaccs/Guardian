
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <out/shared.h>*/
/*#include <out/function_queue/submit_let_new.h>*/

/*#include <parameter/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <type_check/unresolved/foreach.h>*/

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "print_source.h"

struct stringtree* let_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_let);
	
/*	struct stringtree* tree = new_stringtree();*/
	
/*	struct let_expression* this = (void*) super;*/
	
	// iterate through subvariables adding to named-type-tree
	TODO;
	
	// create new environment
	TODO;
	
	// evaluate each one, adding to environment
	TODO;
	
	// evaluate body in new environment
	TODO;
	
	// free environment
	TODO;
	
	// return result;
	TODO;
	
	EXIT;
/*	return tree;*/
}

















