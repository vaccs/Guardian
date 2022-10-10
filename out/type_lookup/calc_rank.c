
#include <debug.h>

#include <out/type/struct.h>
#include <out/type/compare.h>

#include "node/struct.h"

#include "struct.h"

struct heap* type_lookup_calc_rank(
	struct type_lookup* this)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct type_lookup_node* e = node->item;
		
		quack_append(todo, e->otype);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct out_type* otype = quack_pop(todo);
		
		assert(otype);
		
		unsigned rank = 0;
		
		ptrset_foreach(otype->dependent_on, ({
			void runme(void* ptr)
			{
				struct out_type* dep = ptr;
				
				if (rank < dep->rank)
					rank = dep->rank;
			}
			runme;
		}));
		
		rank++;
		
		if (otype->rank != rank)
		{
			ptrset_foreach(otype->dependent_of, ({
				void runme(void* ptr)
				{
					quack_append(todo, ptr);
				}
				runme;
			}));
			
			otype->rank = rank;
		}
	}
	
	struct heap* heap = new_heap(compare_out_types);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct type_lookup_node* e = node->item;
		
		heap_push(heap, e->otype);
	}
	
	free_quack(todo);
	
	EXIT;
	return heap;
}



























