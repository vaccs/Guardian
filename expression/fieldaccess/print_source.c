
#include <debug.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* fieldaccess_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	assert(super->kind == ek_fieldaccess);
	
	struct fieldaccess_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct expression* object = this->object;

	struct type* ftype = super->type;
	struct type* otype = object->type;
	
	type_queue_submit(shared->tqueue, ftype);
	type_queue_submit(shared->tqueue, otype);
	
	stringtree_append_printf(tree, ""
		"({"
			"type_%u* _object = "
	"", otype->id);
	
	struct stringtree* expression = expression_print_source(this->object, shared);
	
	stringtree_append_tree(tree, expression);
	
	struct string* fieldname = this->fieldname;
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, ftype);
	
	stringtree_append_printf(tree, ""
				";"
			"if (!_object.%.*s) {"
				"assert(!\"TODO: missing field!\");"
			"}"
			"type_%u* _field = func_%u(_object.%.*s);"
	"", fieldname->len, fieldname->chars,
	ftype->id, inc_id, fieldname->len, fieldname->chars);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, otype);
	
	stringtree_append_printf(tree, ""
			"func_%u(_object);"
			"_field;"
		"})"
	"", free_id);
	
	free_stringtree(expression);
	
	EXIT;
	return tree;
}














