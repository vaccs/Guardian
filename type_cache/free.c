
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

/*#include <avl/foreach.h>*/
/*#include <avl/free_tree.h>*/

/*#include <type/free.h>*/

/*#include "struct.h"*/
#include "free.h"

void free_type_cache(struct type_cache* this)
{
	ENTER;
	
	TODO;
	#if 0
	avl_foreach(this->tree, ({
		void runme(void* ptr)
		{
			free_type2(ptr);
		}
		runme;
	}));
	
	avl_free_tree(this->tree);
	
	free_type2(this->int_type);
	
	free_type2(this->float_type);
	
	free_type2(this->bool_type);
	
	free(this);
	#endif
	
	EXIT;
}

