
#include <debug.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

/*#include <list/value/struct.h>*/

/*#include "../print_source.h"*/

/*#include <out/get_type_id.h>*/

#include <mpz/struct.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* integer_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct integer_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned tid = out_get_type_id(shared, super->type);
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_printf(tree, "type_%u* new = new_type_%u();", tid, tid);
	
	if (mpz_fits_slong_p(this->integer->mpz))
	{
		signed long val = mpz_get_si(this->integer->mpz);
		
		stringtree_append_printf(tree, "mpz_init_set_si(new->mpz, %lu);", val);
	}
	else
	{
		TODO;
		#if 0
		stringtree_append_printf(tree, "mpz_init_set_str(new->mpz);");
		#endif
	}
	
	stringtree_append_printf(tree, "new;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
	#endif
}

