
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <memory/smalloc.h>

#include <regex/struct.h>

#include <quack/new.h>
#include <quack/is_nonempty.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct node
{
	struct regex* regex;
	unsigned state_id;
};

static int compare_nodes(const void* a, const void* b)
{
	const struct node *A = a, *B = b;
	
	if (A->regex > B->regex)
		return +1;
	else if (A->regex < B->regex)
		return -1;
	else
		return +0;
}

struct stringtree* regex_match_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_regex_match);
	
	struct stringtree* tree = new_stringtree();
	
	struct regex_match_expression* this = (void*) super;
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	{
		stringtree_append_printf(tree, "struct type_%u* string = ", this->string->type->id);
		struct stringtree* subtree = expression_print_source(this->string, shared, environment);
		stringtree_append_tree(tree, subtree);
		free_stringtree(subtree);
		stringtree_append_printf(tree, ";");
	}
	
	stringtree_append_printf(tree, "bool is_accepted = false;");
	stringtree_append_printf(tree, "unsigned i = 0, n = string->len;");
	
	stringtree_append_printf(tree, "goto state_0;");
	
	{
		unsigned next_id = 0;
		
		struct avl_tree_t* lookup = avl_alloc_tree(compare_nodes, free);
		
		struct quack* todo = new_quack();
		
		// setup:
		{
			struct node* node = smalloc(sizeof(*node));
			
			node->regex = this->regex;
			node->state_id = next_id++;
			
			quack_append(todo, node);
			
			avl_insert(lookup, node);
		}
		
		// loop:
		while (quack_is_nonempty(todo))
		{
			struct node* node = quack_pop(todo);
			
			struct regex* regex = node->regex;
			
			stringtree_append_printf(tree, "state_%u: if (i == n) {", node->state_id);
			
			stringtree_append_printf(tree, "goto %s;", regex->accepts ? "accepts" : "rejects");
			
			stringtree_append_printf(tree, "} else switch (string->chars[i++]) {");
			
			for (unsigned i = 0; i < 256; i++)
			{
				struct regex* to = regex->transitions[i];
				
				if (to)
				{
					struct avl_node_t* anode = avl_search(lookup, &to);
					
					if (anode)
					{
						struct node* node = anode->item;
						
						stringtree_append_printf(tree,
							"case %u: goto state_%u; ", i, node->state_id);
					}
					else
					{
						struct node* node = smalloc(sizeof(*node));
						
						node->regex = to;
						node->state_id = next_id++;
						
						quack_append(todo, node);
						
						avl_insert(lookup, node);
						
						stringtree_append_printf(tree,
							"case %u: goto state_%u; ", i, node->state_id);
					}
				}
			}
			
			stringtree_append_printf(tree, "default: goto rejects;");
			
			stringtree_append_printf(tree, "}");
		}
		
		free_quack(todo);
		
		avl_free_tree(lookup);
	}
	
	stringtree_append_printf(tree, "accepts:");
	stringtree_append_printf(tree, "is_accepted = true;");
	
	stringtree_append_printf(tree, "rejects:");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->string->type);
	stringtree_append_printf(tree, "func_%u(string);", free_id);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(is_accepted);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}























