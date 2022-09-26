
#include <debug.h>

#include <named/zebu_expression/struct.h>

#include <quack/new.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/append.h>

#include "resolve_variables.h"

#include "unresolved/new.h"
#include "unresolved/inc.h"
#include "unresolved/len.h"
#include "unresolved/foreach.h"
#include "unresolved/is_nonempty.h"
#include "unresolved/free.h"

#include "specialize/expression.h"

#include "type_check.h"

struct task
{
	struct string* name;
	struct zebu_expression* expression;
	struct unresolved* unresolved;
	unsigned count;
};

static struct task* new_task(
	struct string* name,
	struct zebu_expression* expression,
	struct unresolved* unresolved)
{
	ENTER;
	
	dpvs(name);
	
	struct task* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->expression = expression;
	this->unresolved = inc_unresolved(unresolved);
	
	this->count = unresolved_len(unresolved);
	
	EXIT;
	return this;
}

static void free_task(struct task* this)
{
	TODO;
}

struct dependents
{
	struct string* name;
	struct ptrset* tasks;
};

static struct dependents* new_dependents(
	struct string* name,
	struct task* task)
{
	ENTER;
	
	struct dependents* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->tasks = new_ptrset();
	
	ptrset_add(this->tasks, task);
	
	EXIT;
	return this;
}

static int compare_dependents(const void* a, const void* b)
{
	TODO;
}

static void free_dependents(void* ptr)
{
	// struct dependents* this
	TODO;
}

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* typed_declares,
	struct ptrset* typed_assertions,
	struct avl_tree_t* raw_declares,
	struct ptrset* raw_assertions)
{
	ENTER;
	
	unsigned waiting = 0;
	
	struct quack* ready = new_quack();
	
	struct avl_tree_t* dependents = avl_alloc_tree(compare_dependents, free_dependents);
	
	avl_foreach(raw_declares, ({
		void runme(void* ptr)
		{
			ENTER;
			
			struct named_zebu_expression* nzexpression = ptr;
			
			dpvs(nzexpression->name);
			
			struct unresolved* unresolved = new_unresolved();
			
			resolve_variables(unresolved, tcache, nzexpression->expression);
			
			unresolved_foreach(unresolved, ({
				void runme(struct string* name)
				{
					dpvs(name);
					
					struct avl_node_t* node = avl_search(grammar_types, &name);
					
					if (node)
					{
						// if its in `grammar_types`:
							// assign it, remove it.
						TODO;
					}
				}
				runme;
			}));
			
			struct task* task = new_task(nzexpression->name, nzexpression->expression, unresolved);
			
			if (unresolved_is_nonempty(unresolved))
			{
				unresolved_foreach(unresolved, ({
					void runme(struct string* name)
					{
						dpvs(name);
						
						struct avl_node_t* node = avl_search(dependents, &name);
						
						if (node)
						{
							TODO;
						}
						else
						{
							struct dependents* new = new_dependents(name, task);
							avl_insert(dependents, new);
						}
					}
					runme;
				}));
				
				waiting++;
			}
			else
			{
				quack_append(ready, task);
			}
			
			free_unresolved(unresolved);
			
			EXIT;
		}
		runme;
	}));
	
	while (quack_is_nonempty(ready))
	{
		struct task* task = quack_pop(ready);
		
		unresolved_foreach(task->unresolved, ({
			void runme(struct string* name)
			{
				dpvs(name);
				
				struct avl_node_t* node = avl_search(typed_declares, &name);
				
				assert(node);
				
				TODO;
			}
			runme;
		}));
		
		struct expression* typed = specialize_expression(tcache, task->expression);
		
		TODO;
		// type-check/specialize expression
			// will create new expression structs with types
			// might do some constant-folding
		
		TODO;
		// add specialized expression to `typed_declares`
		
		
		TODO;
		// for d in dependents[me]:
			// if (!--d.count):
				// ready.append(d);
				// waiting--;
		TODO;
	}
	
	if (waiting)
	{
		// "circular reference detected!"
		TODO;
	}
	
	// for all assertions:
		// type-check/specialize expression
	
	TODO;
	
	EXIT;
}





















