
#include <assert.h>

#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

/*#include <out/shared.h>*/
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
/*#include <out/function_queue/submit_inc.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/

#include "struct.h"
#include "generate_append_func.h"

struct stringtree* dict_type_generate_append_func(
	struct dict_type* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* text = new_stringtree();
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->element_type);
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* dict, struct type_%u* element)"
		"{"
			"if (dict->n == dict->cap)"
			"{"
				"dict->cap = dict->cap << 1 ?: 1;"
				"dict->data = realloc(dict->data, sizeof(*dict->data) * dict->cap);"
			"}"
			"dict->data[dict->n++] = func_%u(element);"
		"}"
	"", func_id, this->super.id, this->element_type->id, inc_id);
	
	EXIT;
	return text;
	#endif
}

