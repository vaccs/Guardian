
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include <string/inc.h>
#include <string/compare.h>
#include <string/free.h>

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/foreach.h>
#include <quack/append.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/foreach.h>
#include <set/ptr/free.h>

#include <assertion/new.h>

#include <value/bool/struct.h>

#include <type/struct.h>
#include <type/free.h>

#include <expression/print.h>
#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/free.h>

#include <named/zebu_type/struct.h>

#include <named/type/struct.h>
#include <named/type/new.h>

#include <named/expression/struct.h>
#include <named/expression/new.h>

#include <named/zebu_expression/struct.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <parse/assertion/struct.h>

#include <type_cache/get_type/list.h>

#include "resolve_variables.h"

#include "unresolved/new.h"
#include "unresolved/inc.h"
#include "unresolved/len.h"
#include "unresolved/resolve.h"
#include "unresolved/foreach.h"
#include "unresolved/is_nonempty.h"
#include "unresolved/free.h"

#include "specialize/expression.h"
#include "specialize/shared.h"

#include "build_type.h"
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
	
	dpv(this->count);
	
	EXIT;
	return this;
}

static void free_task(struct task* this)
{
	ENTER;
	
	free_string(this->name);
	
	free_unresolved(this->unresolved);
	
	free(this);
	
	EXIT;
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
	const struct dependents *A = a, *B = b;
	
	return compare_strings(A->name, B->name);
}

static void free_dependents(void* ptr)
{
	struct dependents *dep = ptr;
	
	free_string(dep->name);
	
	free_ptrset(dep->tasks);
	
	free(dep);
}

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	
	struct avl_tree_t* typed_declares,
	struct quack* typed_assertions,
	
	struct avl_tree_t* raw_forwards,
	struct avl_tree_t* raw_declares,
	struct quack* raw_assertions)
{
	ENTER;
	
	struct avl_tree_t* typed_forwards = avl_alloc_tree(compare_named_types, free_named_type);
	
	avl_foreach(raw_forwards, ({
		void runme(void* ptr)
		{
			struct named_zebu_type* nztype = ptr;
			
			struct type* type = build_type(tcache, nztype->type);
			
			avl_insert(typed_forwards, new_named_type(nztype->name, type));
		}
		runme;
	}));
	
	unsigned waiting = 0;
	
	struct specialize_shared sshared = {};
	
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
					ENTER;
					
					dpvs(name);
					
					struct avl_node_t* node = avl_search(grammar_types, &name);
					
					if (node)
					{
						struct named_type* ntype = node->item;
						
						struct type* list = type_cache_get_list_type(tcache, ntype->type);
						
						unresolved_resolve(unresolved, ntype->name, vek_grammar_rule, list, NULL);
					}
					else
					{
						node = avl_search(typed_forwards, &name);
						
						if (node)
						{
							struct named_type* ntype = node->item;
							
							unresolved_resolve(unresolved, ntype->name, vek_forward, ntype->type, NULL);
						}
					}
					
					EXIT;
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
				
				ddprintf("going into waiting...\n");
				
				waiting++;
			}
			else
			{
				ddprintf("going into ready...\n");
				quack_append(ready, task);
			}
			
			// CHECK_NTH(4);
			
			free_unresolved(unresolved);
			
			EXIT;
		}
		runme;
	}));
	
	while (quack_is_nonempty(ready))
	{
		struct task* task = quack_pop(ready);
		
		assert(!task->count);
		
		unresolved_foreach(task->unresolved, ({
			void runme(struct string* name)
			{
				dpvs(name);
				
				struct avl_node_t* node = avl_search(typed_declares, &name);
				
				assert(node);
				
				struct named_expression *ne = node->item;
				
				struct expression* e = ne->expression;
				
				if (e->kind == ek_literal)
				{
					struct literal_expression* le = (void*) e;
					
					unresolved_resolve(task->unresolved, name, vek_declare, e->type, le->value);
				}
				else
				{
					unresolved_resolve(task->unresolved, name, vek_declare, e->type, NULL);
				}
			}
			runme;
		}));
		
		struct expression* typed = specialize_expression(tcache, &sshared, task->expression);
		
		expression_print(typed), puts("");
		
		struct named_expression* declare = new_named_expression(task->name, typed);
		
		struct avl_node_t* node = avl_search(typed_forwards, &task->name);
		
		if (node)
		{
			struct named_type* ntype = node->item;
			
			if (ntype->type != typed->type)
			{
				TODO;
				exit(1);
			}
		}
		
		struct avl_node_t* in = avl_insert(typed_declares, declare);
		
		assert(in);
		
		node = avl_search(dependents, &task->name);
		
		if (node)
		{
			struct dependents* deps = node->item;
			
			ptrset_foreach(deps->tasks, ({
				void runme(void* ptr)
				{
					struct task* task = ptr;
					
					if (!--task->count)
					{
						quack_append(ready, task);
						waiting--;
					}
				}
				runme;
			}));
		}
		
		free_task(task);
		
		free_expression(typed);
	}
	
	if (waiting)
	{
		fprintf(stderr, ""
			"maia: cannot resolve declarations with uses!" "\n"
			"This may be caused by either a missing declaration, or a circular reference" "\n"
		"");
		exit(1);
	}
	
	quack_foreach(raw_assertions, ({
		void runme(void* ptr)
		{
			struct raw_assertion* raw_assertion = ptr;
			
			struct unresolved* unresolved = new_unresolved();
			
			resolve_variables(unresolved, tcache, raw_assertion->expression);
			
			unresolved_foreach(unresolved, ({
				void runme(struct string* name)
				{
					dpvs(name);
					
					struct avl_node_t* node = avl_search(typed_declares, &name);
					
					if (!node)
					{
						TODO;
						exit(1);
					}
					
					struct named_expression *ne = node->item;
					
					struct expression* e = ne->expression;
					
					if (e->kind == ek_literal)
					{
						struct literal_expression* le = (void*) e;
						
						unresolved_resolve(unresolved, name, vek_declare, e->type, le->value);
					}
					else
					{
						unresolved_resolve(unresolved, name, vek_declare, e->type, NULL);
					}
				}
				runme;
			}));
			
			struct expression* specialized = specialize_expression(tcache, &sshared, raw_assertion->expression);
			
			expression_print(specialized), puts("");
			
			if (specialized->type->kind != tk_bool)
			{
				fprintf(stderr, "%s: every assertion should return a bool!\n", argv0);
				exit(e_bad_input_file);
			}
			
			if (specialized->kind == ek_literal)
			{
				struct literal_expression* literal = (void*) specialized;
				
				struct bool_value* value = (struct bool_value*) literal->value;
				
				if (!value->value)
				{
					fprintf(stderr, "%s: assertion constant-folded to false value!\n", argv0);
					exit(e_bad_input_file);
				}
			}
			else
			{
				struct assertion* assertion = new_assertion(raw_assertion->kind, specialized);
				
				quack_append(typed_assertions, assertion);
			}
			
			free_expression(specialized);
			
			free_unresolved(unresolved);
		}
		runme;
	}));
	
	avl_free_tree(dependents);
	
	avl_free_tree(typed_forwards);
	
	free_quack(ready);
	
	EXIT;
}



















