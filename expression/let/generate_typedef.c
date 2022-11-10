
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/

/*#include <type/struct.h>*/

/*#include <type_check/unresolved/foreach.h>*/

/*#include <out/type_queue/submit.h>*/

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* let_expression_generate_generate_typedef(
	struct let_expression* this,
	struct subtype_queue* stqueue,
	struct type_queue* tqueue)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	// type_queue_submit(shared->stqueue, this);
	
	unsigned super_id = this->super.type->id;
	
	unsigned let_id = this->id;
	
	stringtree_append_printf(tree, ""
		"struct subtype_%u"
		"{"
			"struct type_%u super;"
	"", let_id, super_id);
	
	capture_list_foreach(this->captured, ({
		void runme(struct capture* capture)
		{
			dpvs(capture->name);
			
			type_queue_submit(tqueue, capture->type);
			
			struct string* name = capture->name;
			
			stringtree_append_printf(tree, ""
				"struct type_%u* $%.*s;"
			"", capture->type->id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
		"};"
	"");
	
	EXIT;
	return tree;
	#endif
}









