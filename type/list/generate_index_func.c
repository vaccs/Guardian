
#include <debug.h>

/*#include <out/function_lookup/lookup_inc.h>*/
#include <out/function_queue/submit_inc.h>

#include "struct.h"
#include "generate_index_func.h"

struct stringtree* list_type_generate_index_func(
	struct list_type* this,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	unsigned inc_id = function_queue_submit_inc(flookup, this->element_type);
	
	stringtree_append_printf(text, ""
		"type_%u* func_%u(type_%u* list, unsigned index)"
		"{"
			"if (index < list->n)"
			"{"
				"return func_%u(list->data[index]);"
			"}"
			"else"
			"{"
				"assert(!\"index out of bounds\");"
			"}"
		"}"
	"", this->element_type->id, func_id, this->super.id, inc_id);
	
	EXIT;
	return text;
}

