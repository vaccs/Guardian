
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

/*#include <defines/argv0.h>*/

/*#include <enums/error.h>*/

/*#include <memory/smalloc.h>*/

/*#include <string/inc.h>*/
/*#include <string/compare.h>*/
/*#include <string/free.h>*/

/*#include <avl/alloc_tree.h>*/
/*#include <avl/foreach.h>*/
/*#include <avl/insert.h>*/
/*#include <avl/search.h>*/
/*#include <avl/free_tree.h>*/

/*#include <quack/new.h>*/
/*#include <quack/pop.h>*/
/*#include <quack/is_nonempty.h>*/
/*#include <quack/foreach.h>*/
/*#include <quack/append.h>*/
/*#include <quack/free.h>*/

/*#include <set/ptr/new.h>*/
/*#include <set/ptr/add.h>*/
/*#include <set/ptr/foreach.h>*/
/*#include <set/ptr/free.h>*/

/*#include <assertion/new.h>*/

/*#include <value/bool/struct.h>*/

/*#include <type/struct.h>*/
/*#include <type/free.h>*/

/*#include <expression/print.h>*/
#include <expression/struct.h>
#include <expression/literal/struct.h>
/*#include <expression/free.h>*/

/*#include <named/zebu_type/struct.h>*/

#include <named/type/struct.h>
/*#include <named/type/new.h>*/

/*#include <named/expression/struct.h>*/
#include <named/expression/new.h>
#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <named/zebu_expression/struct.h>

/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

/*#include <parse/assertion/struct.h>*/

/*#include <type_cache/get_type/list.h>*/

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <list/zebu_expression/new.h>
#include <list/zebu_expression/append.h>
#include <list/zebu_expression/free.h>

#include "unresolved/new.h"
#include "unresolved/inc.h"
/*#include "unresolved/len.h"*/
#include "unresolved/discard.h"
#include "unresolved/resolve.h"
#include "unresolved/foreach.h"
/*#include "unresolved/is_nonempty.h"*/
#include "unresolved/free.h"

#include "specialize/expression.h"
#include "specialize/shared.h"

#include "determine_type/expression.h"

#include "resolve_variables.h"

#include "determine_direct_uses.h"

/*#include "build_type.h"*/
#include "type_check.h"

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types, // named types?
	
	struct avl_tree_t* raw_declares, // named_zebu_expression
	struct quack* raw_assertions // ptrset of zebu_expressions?
	
/*	struct avl_tree_t* typed_declares,*/
/*	struct quack* typed_assertions,*/
	)
{
	ENTER;
	
	struct avl_tree_t* name_to_type = avl_alloc_tree(compare_named_types, free_named_type);
	
	struct string_list* source_order = new_string_list();
	
	{
		struct task
		{
			struct string* name;
			struct zebu_expression* expression;
			unsigned count;
		};
		
		struct task* new_task(
			struct string* name,
			struct zebu_expression* expression,
			unsigned count)
		{
			ENTER;
			
			dpvs(name);
			
			struct task* this = smalloc(sizeof(*this));
			
			this->name = inc_string(name);
			this->expression = expression;
			this->count = count;
			
			EXIT;
			return this;
		}
		
		void free_task(struct task* this)
		{
			ENTER;
			
			free_string(this->name);
			
			free(this);
			
			EXIT;
		}
		
		struct dependents
		{
			struct string* name;
			struct ptrset* tasks;
		};
		
		struct dependents* new_dependents(
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
		
		int compare_dependents(const void* a, const void* b)
		{
			const struct dependents *A = a, *B = b;
			
			return compare_strings(A->name, B->name);
		}
		
		void free_dependents(void* ptr)
		{
			struct dependents *dep = ptr;
			
			free_string(dep->name);
			
			free_ptrset(dep->tasks);
			
			free(dep);
		}
		
		struct avl_tree_t* dependents = avl_alloc_tree(compare_dependents, free_dependents);
		
		struct quack* ready = new_quack();
		
		struct ptrset* wait = new_ptrset();
		
		avl_foreach(raw_declares, ({
			void runme(void* ptr)
			{
				struct named_zebu_expression* nexp = ptr;
				
				dpvs(nexp->name);
				
				if (verbose)
				{
					struct string* name = nexp->name;
					
					printf("%s: determining direct variable usages of '%.*s'...\n", argv0, name->len, name->chars);
				}
				
				struct stringset* direct_uses = new_stringset();
				
				determine_direct_uses(direct_uses, nexp->expression);
				
				stringset_filter(direct_uses, ({
					bool filter(struct string* element)
					{
						return !avl_search(grammar_types, &element);
					}
					filter;
				}));
				
				if (stringset_is_nonempty(direct_uses))
				{
					if (verbose)
					{
						stringset_foreach(direct_uses, ({
							void runme(struct string* element)
							{
								printf("\t" "'%.*s' is needed\n", element->len, element->chars);
							}
							runme;
						}));
					}
					
					struct task* task = new_task(nexp->name, nexp->expression, stringset_len(direct_uses));
					
					stringset_foreach(direct_uses, ({
						void runme(struct string* name)
						{
							dpvs(name);
							
							struct avl_node_t* node = avl_search(dependents, &name);
							
							if (node)
							{
								struct dependents* dep = node->item;
								ptrset_add(dep->tasks, task);
							}
							else
							{
								struct dependents* dep = new_dependents(name, task);
								avl_insert(dependents, dep);
							}
						}
						runme;
					}));
					
					ptrset_add(wait, task);
				}
				else
				{
					printf("\t" "nothing is needed\n");
					
					quack_append(ready, new_task(nexp->name, nexp->expression, 0));
				}
				
				free_stringset(direct_uses);
			}
			runme;
		}));
		
		while (quack_is_nonempty(ready))
		{
			struct task* task = quack_pop(ready);
			
			struct string* name = task->name;
			
			#ifdef VERBOSE
			printf("%s: determining type of '%.*s': ", argv0, name->len, name->chars);
			#endif
			
			struct type* type = determine_type_of_expression(task->expression, tcache, grammar_types, name_to_type);
			
			#ifdef VERBOSE
			type_print(type), puts("");
			#endif
			
			struct named_type* ntype = new_named_type(name, type);
			
			avl_insert(name_to_type, ntype);
			
			string_list_append(source_order, name);
			
			struct avl_node_t* node = avl_search(dependents, &name);
			
			if (node)
			{
				struct dependents* dependents = node->item;
				
				ptrset_foreach(dependents->tasks, ({
					void runme(void* ptr)
					{
						struct task* task = ptr;
						
						if (!--task->count)
						{
							quack_append(ready, task);
							
							ptrset_discard(wait, ptr);
							
							printf("%s: added '%.*s' to the ready queue\n", argv0, task->name->len, task->name->chars);
						}
					}
					runme;
				}));
			}
			
			free_task(task);
		}
		
		if (ptrset_is_nonempty(wait))
		{
			// "direct circular reference!"
			TODO;
		}
		
		avl_free_tree(dependents);
		
		free_ptrset(wait);
		
		free_quack(ready);
	}
	
	struct avl_tree_t* name_to_expression = avl_alloc_tree(compare_named_expressions, free_named_expression);
	
	{
		struct task
		{
			struct string* name;
			struct zebu_expression* expression;
			struct unresolved* unresolved;
		};
		
		struct task* new_task(
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
			
			EXIT;
			return this;
		}
		
		void free_task(struct task* this)
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
		
		struct dependents* new_dependents(
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
		
		int compare_dependents(const void* a, const void* b)
		{
			const struct dependents *A = a, *B = b;
			
			return compare_strings(A->name, B->name);
		}
		
		void free_dependents(void* ptr)
		{
			struct dependents *dep = ptr;
			
			free_string(dep->name);
			
			free_ptrset(dep->tasks);
			
			free(dep);
		}
		
		struct {
			struct task** data;
			unsigned n, cap;
		} tasks = {};
		
		struct avl_tree_t* dependents = avl_alloc_tree(compare_dependents, free_dependents);
		
		struct quack* todo = new_quack();
		
		struct ptrset* queued = new_ptrset();
		
		avl_foreach(raw_declares, ({
			void runme(void* ptr)
			{
				struct named_zebu_expression* nexp = ptr;
				
				struct unresolved* unresolved = new_unresolved();
				
				resolve_variables(unresolved, tcache, nexp->expression);
				
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
							
							unresolved_resolve_type(unresolved, ntype->name, vek_grammar_rule, list);
							
							unresolved_discard(unresolved, ntype->name);
						}
						
						EXIT;
					}
					runme;
				}));
				
				struct task* task = new_task(nexp->name, nexp->expression, unresolved);
				
				unresolved_foreach(unresolved, ({
					void runme(struct string* name)
					{
						dpvs(name);
						
						struct avl_node_t* node;
						
						if ((node = avl_search(dependents, &name)))
						{
							struct dependents* dep = node->item;
							ptrset_add(dep->tasks, task);
						}
						else
						{
							struct dependents* dep = new_dependents(name, task);
							avl_insert(dependents, dep);
						}
						
						node = avl_search(name_to_type, &name);
						
						if (!node)
						{
							// "could not find defintition for {name}"!
							TODO;
							exit(1);
						}
						
						struct named_type* ntype = node->item;
						
						unresolved_resolve_type(unresolved, name, vek_declare, ntype->type);
					}
					runme;
				}));
				
				// add task to `tasks`, `queued` and `todo`
				if (tasks.n == tasks.cap)
				{
					tasks.cap = tasks.cap << 1 ?: 1;
					tasks.data = srealloc(tasks.data, sizeof(*tasks.data) * tasks.cap);
				}
				
				tasks.data[tasks.n++] = task;
				
				quack_append(todo, task);
				ptrset_add(queued, task);
				
				free_unresolved(unresolved);
			}
			runme;
		}));
		
		struct specialize_shared sshared = {};
		
		while (quack_is_nonempty(todo))
		{
			struct task* task = quack_pop(todo);
			
			printf("%s: specializing '%.*s'...\n", argv0, task->name->len, task->name->chars);
			
			struct expression* typed = specialize_expression(tcache, &sshared, task->expression);
			
			struct avl_node_t* node;
			
			#ifndef NDEBUG
			node = avl_search(name_to_type, &task->name);
			assert(node);
			struct named_type* ntype = node->item;
			assert(ntype->type == typed->type);
			#endif
			
			if ((node = avl_search(name_to_expression, &task->name)))
			{
				// free(dict[exp]);
				// dict[exp] = typed;
				TODO;
			}
			else
			{
				struct named_expression* new = new_named_expression(task->name, typed);
				
				avl_insert(name_to_expression, new);
			}
			
			if (typed->kind == ek_literal)
			{
				struct literal_expression* literal = (void*) typed;
				
				node = avl_search(dependents, &task->name);
				
				if (node)
				{
					struct dependents* dep = node->item;
					
					ptrset_foreach(dep->tasks, ({
						void runme(void* ptr)
						{
							struct task* task = ptr;
							
							unresolved_resolve_value(task->unresolved, task->name, literal->value);
							
							if (ptrset_add(queued, ptr))
							{
								// todo.append(using-expression);
								TODO;
							}
						}
						runme;
					}));
				}
			}
			
			ptrset_discard(queued, task);
		}
		
		while (tasks.n--)
		{
			TODO; // free tasks
		}
		
		free_ptrset(queued);
		
		free_quack(todo);
		
		avl_free_tree(dependents);
	}
	
	// declarations = list();
	TODO;
	
	// for e in source-order:
		// assert(e in dict);
		// typed = dict[e];
		// if not typed is literal:
			// declarations.append(typed);
	TODO;
	
	// assertions = list();
	TODO;
	
	// for a in raw-assertions:
		// typed = specialize(a);
		// assertions.append(typed);
	TODO;
	
	free_string_list(source_order);
	
	avl_free_tree(name_to_expression);
	
	avl_free_tree(name_to_type);
	
	EXIT;
}




	#if 0
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
	#endif
	










