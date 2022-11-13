
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>
#include <type/environment/struct.h>

/*#include <out/type_queue/submit.h>*/

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* lambda_expression_generate_generate_typedef(
	struct lambda_expression* this,
	struct subtype_queue* stqueue,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"struct subtype_%u"
		"{"
			"struct type_%u super;"
			"struct type_%u* prev;"
		"};"
	"", this->id, this->super.type->id, this->environment->prev->super.id);
	
	EXIT;
	return tree;
}




























