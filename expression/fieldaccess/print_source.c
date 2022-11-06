
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <string/struct.h>

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
			"struct type_%u* object = "
	"", otype->id);
	
	struct stringtree* expression = expression_print_source(this->object, shared);
	
	stringtree_append_tree(tree, expression);
	
	struct string* fieldname = this->fieldname;
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, ftype);
	
	stringtree_append_printf(tree, ""
				";"
			"if (!object->$%.*s) {"
				"assert(!\"TODO: missing field!\");"
			"}"
			"struct type_%u* field = func_%u(object->$%.*s);"
	"", fieldname->len, fieldname->chars,
	ftype->id, inc_id, fieldname->len, fieldname->chars);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, otype);
	
	stringtree_append_printf(tree, ""
			"func_%u(object);"
			"field;"
		"})"
	"", free_id);
	
	free_stringtree(expression);
	
	EXIT;
	return tree;
}














