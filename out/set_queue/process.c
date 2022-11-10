
#include <assert.h>

#include <debug.h>

/*#include <avl/search.h>*/

/*#include <string/struct.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/

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
	
	TODO;
	#if 0
	this->init_text = new_stringtree();
	
	this->assign_text = new_stringtree();
	
	this->uninit_text = new_stringtree();
	
	// generate text for declaring lists of grammar data
	stringset_foreach(grammar_sets, ({
		void runme(struct string* name)
		{
			dpvs(name);
			
			struct avl_node_t* node = avl_search(grammar_types, &name);
			
			assert(node);
			
			struct named_type* ntype = node->item;
			
			struct type* type = ntype->type;
			
			struct type* ltype = type_cache_get_list_type(shared->tcache, type);
			
			type_queue_submit(shared->tqueue, ltype);
			
			unsigned new_id = function_queue_submit_new(shared->fqueue, ltype);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, ltype);
			
			stringtree_append_printf(this->init_text, ""
				"struct type_%u* $%.*s = NULL;"
			"", ltype->id, name->len, name->chars);
			
			stringtree_append_printf(this->assign_text, ""
				"$%.*s = func_%u();"
			"", name->len, name->chars, new_id);
			
			stringtree_append_printf(this->uninit_text, ""
				"func_%u($%.*s);"
			"", free_id, name->len, name->chars);
		}
		runme;
	}));
	#endif
	
	EXIT;
}












