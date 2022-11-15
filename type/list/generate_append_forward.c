
#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

/*#include <out/shared.h>*/
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
/*#include <out/function_queue/submit_inc.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_append_forward.h"

struct stringtree* list_type_generate_append_forward(
	struct list_type* this,
	unsigned func_id)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"auto void func_%u(struct type_%u* list, struct type_%u* element);"
	"", func_id, this->super.id, this->element_type->id);
	
	EXIT;
	return text;
}

