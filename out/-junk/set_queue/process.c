
#include <assert.h>

#include <debug.h>

/*#include <avl/search.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <set/string/foreach.h>*/

/*#include <named/type/struct.h>*/

/*#include <type_cache/get_type/list.h>*/

/*#include <type/struct.h>*/
/*#include <type/free.h>*/

/*#include "../shared.h"*/
/*#include "../type_queue/submit.h"*/
/*#include "../function_queue/submit_new.h"*/
/*#include "../function_queue/submit_free.h"*/

#include "struct.h"
#include "process.h"

void set_queue_process(
	struct set_queue* this,
	struct avl_tree_t* grammar_types,
	struct stringset* grammar_sets,
	struct out_shared* shared)
{
	ENTER;
	
	this->text = new_stringtree();
	
	EXIT;
}










