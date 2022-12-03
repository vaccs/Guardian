
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/foreach.h>

#include <named/type/struct.h>
#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <parse/raw_statement/struct.h>

#include <type/print.h>
#include <type/struct.h>

#include <value/bool/struct.h>

#include <string/struct.h>

#include <named/expression/new.h>
#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <expression/literal/struct.h>
#include <expression/struct.h>
#include <expression/print.h>
#include <expression/free.h>

#include <list/statement/append.h>

#include <statement/free.h>

#include <list/raw_statement/foreach.h>

#include <type_cache/get_list_type.h>
#include <type_cache/get_string_type.h>

#include <statement/assert/new.h>
#include <statement/declare/new.h>
#include <statement/print/new.h>
#include <statement/parse/new.h>
#include <statement/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

#ifdef VERBOSE
#include <cmdln/verbose.h>
#endif

#include "scope/layer.h"
#include "scope/struct.h"
#include "scope/new.h"
#include "scope/push.h"
#include "scope/declare.h"
#include "scope/lookup.h"
#include "scope/pop.h"
#include "scope/free.h"

#include "specialize/expression.h"

#include "determine_type/expression.h"

#include "type_check.h"

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types, // named types
	struct raw_statement_list* raw_statements,
	struct statement_list* statements)
{
	ENTER;
	
	struct type_check_scope* scope = new_type_check_scope();
	
	type_check_scope_push(scope);
	
	avl_foreach(grammar_types, ({
		void runme(void* ptr)
		{
			struct named_type* ntype = ptr;
			
			struct type* ltype = type_cache_get_list_type(tcache, ntype->type);
			
			type_check_scope_declare(scope, ntype->name, ltype);
		}
		runme;
	}));
	
	raw_statement_list_foreach(raw_statements, ({
		void runme(struct raw_statement* raw_statement)
		{
			switch (raw_statement->kind)
			{
				case rsk_assertion:
					break;
				
				case rsk_declaration:
				{
					struct string* name = raw_statement->name;
					
					struct type* type = determine_type_of_expression(
						raw_statement->expression, tcache, scope);
					
					#ifdef VERBOSE
					if (verbose)
					{
						struct stringtree* tree = new_stringtree();
						
						stringtree_append_printf(tree, "%s: type of '%.*s' is: ",
							argv0, name->len, name->chars);
						
						struct stringtree* subtree = type_print2(type);
						
						stringtree_append_tree(tree, subtree);
						
						stringtree_append_printf(tree, "\n");
						
						stringtree_stream(tree, stdout);
						
						free_stringtree(subtree);
						free_stringtree(tree);
					}
					#endif
					
					type_check_scope_declare(scope, name, type);
					break;
				}
				
				case rsk_print:
					break;
				
				case rsk_parse:
					break;
				
				default:
					TODO;
					break;
			}
		}
		runme;
	}));
	
	raw_statement_list_foreach(raw_statements, ({
		void runme(struct raw_statement* raw_statement)
		{
			switch (raw_statement->kind)
			{
				case rsk_assertion:
				{
					struct expression* specialized = specialize_expression(
						tcache, scope, raw_statement->expression);
					
					#ifdef VERBOSE
					if (verbose)
					{
						struct stringtree* tree = new_stringtree();
						
						stringtree_append_printf(tree,
							"%s: specialized assert statement on line %u: ",
							argv0, raw_statement->line);
						
						struct stringtree* subtree = expression_print2(specialized);
						
						stringtree_append_tree(tree, subtree);
						
						stringtree_append_printf(tree, "\n");
						
						stringtree_stream(tree, stdout);
						
						free_stringtree(tree);
						free_stringtree(subtree);
					}
					#endif
					
					if (specialized->type->kind != tk_bool)
					{
						TODO;
						exit(1);
					}
					
					if (specialized->kind == ek_literal)
					{
						struct literal_expression* literal = (void*) specialized;
						
						struct bool_value* value = (void*) literal->value;
						
						if (raw_statement->assertion_kind == ak_error && !value->value)
						{
							fflush(stdout);
							fprintf(stderr, "%s: %%error: assertion constant-folded to false!\n", argv0);
							exit(1);
						}
					}
					else
					{
						struct statement* statement = new_assert_statement(
							raw_statement->line,
							raw_statement->assertion_kind, specialized);
						
						statement_list_append(statements, statement);
						
						free_statement(statement);
					}
					
					free_expression(specialized);
					break;
				}
				
				case rsk_declaration:
				{
					struct string* name = raw_statement->name;
					
					struct expression* specialized = specialize_expression(
						tcache, scope, raw_statement->expression);
					
					#ifdef VERBOSE
					if (verbose)
					{
						struct stringtree* tree = new_stringtree();
						
						stringtree_append_printf(tree,
							"%s: specialized '%.*s' declaration: ",
							argv0, name->len, name->chars);
						
						struct stringtree* subtree = expression_print2(specialized);
						
						stringtree_append_tree(tree, subtree);
						
						stringtree_append_printf(tree, "\n");
						
						stringtree_stream(tree, stdout);
						
						free_stringtree(tree);
						free_stringtree(subtree);
					}
					#endif
					
					if (specialized->kind == ek_literal)
					{
						struct literal_expression* spef = (void*) specialized;
						
						type_check_scope_declare_value(scope, name, spef->value);
					}
					
					struct statement* statement = new_declare_statement(
						name, specialized);
					
					statement_list_append(statements, statement);
					
					free_statement(statement);
					
					free_expression(specialized);
					break;
				}
				
				case rsk_print:
				{
					struct expression* specialized = specialize_expression(
						tcache, scope, raw_statement->expression);
					
					#ifdef VERBOSE
					if (verbose)
					{
						struct stringtree* tree = new_stringtree();
						
						stringtree_append_printf(tree,
							"%s: specialized print statement: ",
							argv0);
						
						struct stringtree* subtree = expression_print2(specialized);
						
						stringtree_append_tree(tree, subtree);
						
						stringtree_append_printf(tree, "\n");
						
						stringtree_stream(tree, stdout);
						
						free_stringtree(tree);
						free_stringtree(subtree);
					}
					#endif
					
					struct statement* statement = new_print_statement(specialized);
					
					statement_list_append(statements, statement);
					
					free_statement(statement);
					
					free_expression(specialized);
					break;
				}
				
				case rsk_parse:
				{
					struct expression* specialized = NULL;
					
					if (raw_statement->expression)
					{
						specialized = specialize_expression(
							tcache, scope, raw_statement->expression);
						
						#ifdef VERBOSE
						if (verbose)
						{
							struct stringtree* tree = new_stringtree();
							
							stringtree_append_printf(tree,
								"%s: specialized parse statement on line %u: ",
								argv0, raw_statement->line);
							
							struct stringtree* subtree = expression_print2(specialized);
							
							stringtree_append_tree(tree, subtree);
							
							stringtree_append_printf(tree, "\n");
							
							stringtree_stream(tree, stdout);
							
							free_stringtree(tree);
							free_stringtree(subtree);
						}
						#endif
						
						struct type* type = type_cache_get_string_type(tcache);
						
						if (specialized->type != type)
						{
							TODO;
							exit(1);
						}
					}
					
					struct statement* statement = new_parse_statement(
						raw_statement->line, specialized, raw_statement->name, raw_statement->grammar);
					
					statement_list_append(statements, statement);
					
					free_statement(statement);
					
					free_expression(specialized);
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		runme;
	}));
	
	type_check_scope_pop(scope);
	
	free_type_check_scope(scope);
	
	EXIT;
}























