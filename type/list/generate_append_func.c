
#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

#include <out/shared.h>
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
#include <out/function_queue/submit_inc.h>

#include "struct.h"
#include "generate_append_func.h"

struct stringtree* list_type_generate_append_func(
	struct list_type* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->element_type);
	
	stringtree_append_printf(text, ""
		"static void func_%u(struct type_%u* list, struct type_%u* element)"
		"{"
			"if (list->n == list->cap)"
			"{"
				"list->cap = list->cap << 1 ?: 1;"
				"list->data = realloc(list->data, sizeof(*list->data) * list->cap);"
			"}"
			"list->data[list->n++] = func_%u(element);"
		"}"
	"", func_id, this->super.id, this->element_type->id, inc_id);
	
	EXIT;
	return text;
}

