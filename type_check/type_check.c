
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

/*#include <enums/error.h>*/

#include <cmdln/verbose.h>

#include <memory/smalloc.h>

#include <string/struct.h>
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
/*#include <quack/foreach.h>*/
#include <quack/append.h>
#include <quack/free.h>

#include <list/string/struct.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/foreach.h>
#include <set/ptr/discard.h>
#include <set/ptr/is_nonempty.h>
#include <set/ptr/free.h>

#include <set/string/new.h>
#include <set/string/filter.h>
#include <set/string/is_nonempty.h>
#include <set/string/foreach.h>
#include <set/string/free.h>
#include <set/string/len.h>

#include <list/string/append.h>
#include <list/string/index.h>

#include <type_cache/get_type/list.h>

#include <set/string/add.h>

#include <memory/srealloc.h>

#include <list/string/free.h>

/*#include <assertion/new.h>*/

/*#include <value/bool/struct.h>*/

/*#include <type/struct.h>*/
/*#include <type/free.h>*/
#include <type/print.h>

#include <list/string/new.h>

#include <expression/struct.h>
#include <expression/print.h>
#include <expression/inc.h>
#include <expression/literal/struct.h>
#include <expression/free.h>

/*#include <named/zebu_type/struct.h>*/

#include <named/type/struct.h>
/*#include <named/type/new.h>*/

#include <named/expression/struct.h>
#include <named/expression/new.h>
#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <named/zebu_expression/struct.h>

#include <assertion/new.h>
#include <assertion/free.h>

/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

/*#include <parse/assertion/struct.h>*/

/*#include <type_cache/get_type/list.h>*/

#include <set/string/contains.h>
#include <list/string/pop.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <list/assertion/append.h>

#include <list/zebu_expression/new.h>
#include <list/zebu_expression/append.h>
#include <list/zebu_expression/free.h>

#include <list/string/foreach.h>

#include <list/raw_assertion/foreach.h>	

#include <list/declaration/append.h>

#include <declaration/new.h>
#include <declaration/free.h>

#include <parse/assertion/struct.h>

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
	struct raw_assertion_list* raw_assertions, // ptrset of zebu_expressions?
	
	struct stringset* grammar_sets,
	struct declaration_list* declarations,
	struct assertion_list* assertions)
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
				
				#ifdef VERBOSE
				if (verbose)
				{
					struct string* name = nexp->name;
					
					printf("%s: determining direct variable usages of '%.*s':", argv0, name->len, name->chars);
				}
				#endif
				
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
					#ifdef VERBOSE
					if (verbose)
					{
						stringset_foreach(direct_uses, ({
							void runme(struct string* element)
							{
								printf(" %.*s", element->len, element->chars);
							}
							runme;
						}));
						
						puts("");
					}
					#endif
					
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
					printf(" nothing is needed.\n");
					
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
	
	struct stringset* cyclic_variables = new_stringset();

	struct specialize_shared sshared = {};
	
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
		
		int compare_tasks(const void* a, const void* b)
		{
			const struct task* A = a, *B = b;
			return compare_strings(A->name, B->name);
		}
		
		void free_task(void* ptr)
		{
			ENTER;
			
			struct task* this = ptr;
			
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
		
		struct avl_tree_t* dependents = avl_alloc_tree(compare_dependents, free_dependents);
		
		struct avl_tree_t* all_tasks = avl_alloc_tree(compare_tasks, free_task);
		
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
							
							stringset_add(grammar_sets, name);
							
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
							fprintf(stderr, ""
								"%s: could not find defintition"
								" for variable '%.*s'!\n"
							"", argv0, name->len, name->chars);
							exit(1);
						}
						
						struct named_type* ntype = node->item;
						
						assert(ntype->type);
						
						unresolved_resolve_type(unresolved, name, vek_declare, ntype->type);
						
						// CHECK_NTH(9);
					}
					runme;
				}));
				
				avl_insert(all_tasks, task);
				
				quack_append(todo, task);
				
				ptrset_add(queued, task);
				
				free_unresolved(unresolved);
			}
			runme;
		}));
		
		// look for cycles:
		avl_foreach(all_tasks, ({
			void runme(void* ptr)
			{
				struct task* task = ptr;
				
				if (!stringset_contains(cyclic_variables, task->name))
				{
					struct string_list* stack = new_string_list();
					
					printf("%s: looking for cycles starting from '%.*s':\n",
						argv0, task->name->len, task->name->chars);
					
					void helper(struct string* name)
					{
						unsigned index;
						
						if (string_list_index(stack, &index, name))
						{
							dpv(index);
							
							for (unsigned i = index, n = stack->n; i < n; i++)
							{
								struct string* cyclic = stack->data[i];
								
								dpvs(cyclic);
								
								printf("%s: \t '%.*s' is cyclic.\n", argv0, cyclic->len, cyclic->chars);
								
								stringset_add(cyclic_variables, cyclic);
							}
						}
						else
						{
							string_list_append(stack, name);
							
							struct avl_node_t* node = avl_search(all_tasks, &name);
							
							assert(node);
							
							struct task* task = node->item;
							
							unresolved_foreach(task->unresolved, ({
								void runme(struct string* name)
								{
									dpvs(name);
									helper(name);
								}
								runme;
							}));
							
							string_list_pop(stack);
						}
					}
					
					helper(task->name);
					
					free_string_list(stack);
				}
			}
			runme;
		}));
		
		while (quack_is_nonempty(todo))
		{
			struct task* task = quack_pop(todo);
			
			ptrset_discard(queued, task);
			
			printf("%s: specializing '%.*s': ", argv0, task->name->len, task->name->chars);
			
			struct expression* typed = specialize_expression(tcache, &sshared, task->expression);
			
			expression_print(typed);
			
			puts("");
			
			struct avl_node_t* node;
			
			#ifndef NDEBUG
			node = avl_search(name_to_type, &task->name);
			assert(node);
			struct named_type* ntype = node->item;
			assert(ntype->type == typed->type);
			#endif
			
			if ((node = avl_search(name_to_expression, &task->name)))
			{
				struct named_expression* old = node->item;
				
				free_expression(old->expression);
				
				old->expression = inc_expression(typed);
			}
			else
			{
				struct named_expression* new = new_named_expression(task->name, typed);
				
				avl_insert(name_to_expression, new);
			}
			
			if (typed->kind == ek_literal && !stringset_contains(cyclic_variables, task->name))
			{
				struct literal_expression* literal = (void*) typed;
				
				node = avl_search(dependents, &task->name);
				
				if (node)
				{
					struct dependents* dep = node->item;
					
					ptrset_foreach(dep->tasks, ({
						void runme(void* ptr)
						{
							struct task* subtask = ptr;
							
							unresolved_resolve_value(subtask->unresolved, task->name, literal->value);
							
							if (ptrset_add(queued, ptr))
							{
								quack_append(todo, subtask);
							}
						}
						runme;
					}));
				}
			}
			
			free_expression(typed);
		}
		
		free_ptrset(queued);
		
		free_quack(todo);
		
		avl_free_tree(all_tasks);
		
		avl_free_tree(dependents);
	}
	
	string_list_foreach(source_order, ({
		void runme(struct string* name)
		{
			dpvs(name);
			
			struct avl_node_t* node = avl_search(name_to_expression, &name);
			
			assert(node);
			
			struct named_expression* nexpression = node->item;
			
			if (nexpression->expression->kind != ek_literal || stringset_contains(cyclic_variables, nexpression->name))
			{
				struct declaration* declaration = new_declaration(name, nexpression->expression);
				
				declaration_list_append(declarations, declaration);
				
				free_declaration(declaration);
			}
		}
		runme;
	}));
	
	raw_assertion_list_foreach(raw_assertions, ({
		void runme(struct raw_assertion* element)
		{
			ENTER;
			
			dpv(element);
			
			struct unresolved* unresolved = new_unresolved();
			
			resolve_variables(unresolved, tcache, element->expression);
			
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
						
						TODO;
						
						unresolved_resolve_type(unresolved, ntype->name, vek_grammar_rule, list);
						
						unresolved_discard(unresolved, ntype->name);
					}
					else
					{
						node = avl_search(name_to_expression, &name);
						
						if (!node)
						{
							// "could not find defintition for {name}"!
							TODO;
							exit(1);
						}
						
						struct named_expression* nexpression = node->item;
						
						struct expression* expression = nexpression->expression;
						
						if (expression->kind == ek_literal)
						{
							struct literal_expression* literal = (void*) expression;
							
							assert(literal->value);
							
							unresolved_resolve_type(unresolved, name, vek_declare, expression->type);
							unresolved_resolve_value(unresolved, name, literal->value);
						}
						else
						{
							unresolved_resolve_type(unresolved, name, vek_declare, expression->type);
						}
					}
					
					EXIT;
				}
				runme;
			}));
			
			struct expression* typed = specialize_expression(tcache, &sshared, element->expression);
			
			struct assertion* assertion = new_assertion(element->kind, typed);
			
			assertion_list_append(assertions, assertion);
			
			free_expression(typed);
			
			free_assertion(assertion);
			
			free_unresolved(unresolved);
			
			EXIT;
		}
		runme;
	}));
	
	free_stringset(cyclic_variables);
	
	free_string_list(source_order);
	
	avl_free_tree(name_to_expression);
	
	avl_free_tree(name_to_type);
	
	EXIT;
}
























