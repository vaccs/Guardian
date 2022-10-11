
#include <debug.h>

#include <type/free.h>

#include "struct.h"
#include "free.h"

void free_type_cache(struct type_cache* this)
{
	ENTER;
	
	avl_foreach(this->tree, ({
		void runme(void* ptr)
		{
			free_type2(ptr);
		}
		runme;
	}));
	
	avl_free_tree(this->tree);
	
	free_type2(this->int_type);
	free_type2(this->bool_type);
	
	free(this);
	
	EXIT;
}

