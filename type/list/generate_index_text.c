
#include <debug.h>

#include <out/function_lookup/lookup_inc.h>

#include "struct.h"
#include "generate_index_text.h"

struct stringtree* list_type_generate_index_text(
	struct list_type* this,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	unsigned inc_id = function_lookup_inc(flookup, this->element_type, func_id);
	
	stringtree_append_printf(text, ""
		"type_%u* func_%u(type_%u* list, unsigned index)"
		"{"
			"if (index < list->n)"
			"{"
				"return func_%u(list->data[index]);"
			"}"
			"else"
			"{"
				"exit(1);"
			"}"
		"}"
	"", this->element_type->id, func_id, this->super.id, inc_id);
	
	EXIT;
	return text;
}

