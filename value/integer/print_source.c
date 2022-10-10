
#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/append_printf.h>*/

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_new.h>

#include <mpz/struct.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* integer_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct integer_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_lookup(shared->tlookup, super->type, NULL);
	
	stringtree_append_printf(tree, "({");
	
	unsigned tid = super->type->id;
	
	unsigned new_id = function_lookup_new(shared->flookup, super->type);
	
	stringtree_append_printf(tree, "type_%u* new = func_%u();", tid, new_id);
	
	if (mpz_fits_slong_p(this->integer->mpz))
	{
		signed long val = mpz_get_si(this->integer->mpz);
		
		stringtree_append_printf(tree, "mpz_set_si(new->mpz, %li);", val);
	}
	else
	{
		TODO;
		#if 0
		stringtree_append_printf(tree, "mpz_set_str(new->mpz);");
		#endif
	}
	
	stringtree_append_printf(tree, "new;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














