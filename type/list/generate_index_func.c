
#include <debug.h>

#include <type_cache/get_type/int.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
/*#include <out/function_lookup/lookup_inc.h>*/
#include <out/function_queue/submit_inc.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_index_func.h"

struct stringtree* list_type_generate_index_func(
	struct list_type* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	struct type* inttype = type_cache_get_int_type(shared->tcache);
	
	unsigned int_id = inttype->id;
	
	type_queue_submit(shared->tqueue, inttype);
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->element_type);
	
	stringtree_append_printf(text, ""
		"static struct type_%u* func_%u(struct type_%u* list, struct type_%u* index)"
		"{"
			"unsigned native_index;"
			""
			"if (mpz_fits_uint_p(index->value) && (native_index = mpz_get_ui(index->value)) < list->n)"
			"{"
				"return func_%u(list->data[native_index]);"
			"}"
			"else"
			"{"
				"assert(!\"index out of bounds\");"
			"}"
		"}"
	"", this->element_type->id, func_id, this->super.id, int_id, inc_id);
	
	EXIT;
	return text;
}

