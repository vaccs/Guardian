
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>

#include <list/value/foreach.h>

/*#include <out/type_queue/submit.h>*/

#include <out/type_queue/submit.h>

#include <out/function_queue/submit_free.h>

#include <value/print_source.h>

#include <out/function_queue/submit_new.h>

/*#include <mpz/struct.h>*/

#include <misc/value_to_id/add.h>
#include <misc/value_to_id/discard.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* tuple_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct tuple_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "struct type_%u* value_%u = func_%u();", super->type->id, value_id, new_id);
		
		unsigned argcounter = 0;
		
		value_list_foreach(this->subvalues, ({
			void runme(struct value* value)
			{
				stringtree_append_printf(tree, "value_%u->$%u = ", value_id, argcounter);
				
				struct stringtree* subtree = value_print_source(value, shared, vtoi);
				
				stringtree_append_tree(tree, subtree);
				
				stringtree_append_printf(tree, ";");
				
				argcounter++;
				
				free_stringtree(subtree);
			}
			runme;
		}));
		
		stringtree_append_printf(tree, "value_%u;",value_id);
		
		value_to_id_discard(vtoi, super);
	}
	else
	{
		TODO;
	}
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}
















