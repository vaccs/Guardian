
#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include "struct.h"
#include "compare_simplified.h"

struct node
{
	const struct regex* regex;
	unsigned number;
};

static void insert_number(
	struct avl_tree_t* avl,
	const struct regex* regex,
	unsigned number)
{
	ENTER;
	
	struct node* new = smalloc(sizeof(*new));
	
	new->regex = regex;
	new->number = number;
	
	avl_insert(avl, new);
	
	EXIT;
}

static int compare(const void* a, const void* b)
{
	const struct node* A = a, *B = b;
	
	if (A->regex > B->regex)
		return +1;
	else if (A->regex < B->regex)
		return -1;
	
	return 0;
}

struct task
{
	const struct regex* a_node, *b_node;
};

static struct task* new_task(const struct regex* a_node, const struct regex* b_node)
{
	ENTER;
	
	struct task* this = smalloc(sizeof(*this));
	
	this->a_node = a_node;
	this->b_node = b_node;
	
	EXIT;
	return this;
}

int regex_compare_simplified(
	const struct regex* a_start,
	const struct regex* b_start)
{
	int cmp = 0;
	ENTER;
	
	struct avl_tree_t* a_numbers = avl_alloc_tree(compare, free);
	struct avl_tree_t* b_numbers = avl_alloc_tree(compare, free);
	
	struct quack* todo = new_quack();
	
	quack_append(todo, new_task(a_start, b_start));
	
	unsigned next_number = 0;
	
	while (!cmp && quack_is_nonempty(todo))
	{
		struct task* task = quack_pop(todo);
		
		const struct regex* const a = task->a_node;
		const struct regex* const b = task->b_node;
		
		struct avl_node_t* is_a_numbered = avl_search(a_numbers, &a);
		struct avl_node_t* is_b_numbered = avl_search(b_numbers, &b);
		
		dpvb(is_a_numbered);
		dpvb(is_b_numbered);
		
		if (is_a_numbered && is_b_numbered)
		{
			TODO;
			#if 0
			unsigned a_number = ((struct node*) is_a_numbered->item)->number;
			unsigned b_number = ((struct node*) is_a_numbered->item)->number;
			
			dpv(a_number);
			dpv(b_number);
			
			if (a_number > b_number)
				cmp = +1;
			else if (a_number < b_number)
				cmp = -1;
			#endif
		}
		else if (is_a_numbered)
		{
			TODO;
			#if 0
			// b is greater than a:
			cmp = -1;
			#endif
		}
		else if (is_b_numbered)
		{
			TODO;
			#if 0
			// a is greater than b:
			cmp = +1;
			#endif
		}
		else
		{
			insert_number(a_numbers, a, next_number);
			insert_number(b_numbers, b, next_number);
			
			next_number++;
			
			if (!!a->accepts > !!b->accepts)
				cmp = +1;
			else if (!!a->accepts < !!b->accepts)
				cmp = -1;
			
			for (unsigned i = 0, n = 256; !cmp && i < n; i++)
			{
				struct regex* at = a->transitions[i], * bt = b->transitions[i];
				
				if (at)
				{
					if (bt)
						quack_append(todo, new_task(at, bt));
					else
						cmp = +1;
				}
				else if (bt)
					cmp = -1;
			}
			
			assert(!a->lambdas.n);
			assert(!b->lambdas.n);
			
			// possibly compare EOF states
			if (!cmp)
			{
				struct regex* at = a->EOF_transition_to, * bt = b->EOF_transition_to;
				
				if (at)
					if (bt)
						quack_append(todo, new_task(at, bt));
					else
						cmp = +1;
				else if (bt)
					cmp = -1;
			}
		}
		
		free(task);
	}
	
	while (quack_is_nonempty(todo))
	{
		free(quack_pop(todo));
	}
	
	free_quack(todo);
	
	avl_free_tree(a_numbers);
	avl_free_tree(b_numbers);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}






















