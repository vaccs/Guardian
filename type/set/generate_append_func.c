
#include <assert.h>
#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

#include <out/shared.h>
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
#include <out/function_queue/submit_inc.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_append_func.h"

struct stringtree* set_type_generate_append_func(
	struct set_type* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* text = new_stringtree();
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->element_type);
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* set, struct type_%u* element)"
		"{"
			"if (set->n == set->cap)"
			"{"
				"set->cap = set->cap << 1 ?: 1;"
				"set->data = realloc(set->data, sizeof(*set->data) * set->cap);"
			"}"
			"set->data[set->n++] = func_%u(element);"
		"}"
	"", func_id, this->super.id, this->element_type->id, inc_id);
	
	EXIT;
	return text;
	#endif
}

