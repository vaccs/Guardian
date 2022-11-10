
/*#include <enums/error.h>*/

/*#include <cmdln/verbose.h>*/

/*#include <memory/smalloc.h>*/

/*#include <string/struct.h>*/
/*#include <string/inc.h>*/
/*#include <string/compare.h>*/
/*#include <string/free.h>*/

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

/*#include <list/string/struct.h>*/

/*#include <type/struct.h>*/

/*#include <value/bool/struct.h>*/

/*#include <set/ptr/new.h>*/
/*#include <set/ptr/add.h>*/
/*#include <set/ptr/foreach.h>*/
/*#include <set/ptr/discard.h>*/
/*#include <set/ptr/is_nonempty.h>*/
/*#include <set/ptr/free.h>*/

/*#include <set/string/new.h>*/
/*#include <set/string/filter.h>*/
/*#include <set/string/is_nonempty.h>*/
/*#include <set/string/foreach.h>*/
/*#include <set/string/free.h>*/
/*#include <set/string/len.h>*/

/*#include <list/string/append.h>*/
/*#include <list/string/index.h>*/

/*#include <set/string/add.h>*/

/*#include <memory/srealloc.h>*/

/*#include <list/string/free.h>*/

/*#include <assertion/new.h>*/

/*#include <value/bool/struct.h>*/

/*#include <type/struct.h>*/
/*#include <type/free.h>*/

/*#include <list/string/new.h>*/

/*#include <expression/struct.h>*/
/*#include <expression/inc.h>*/
/*#include <expression/literal/struct.h>*/
/*#include <expression/free.h>*/

/*#include <named/zebu_type/struct.h>*/

/*#include <named/type/struct.h>*/
/*#include <named/type/new.h>*/

/*#include <named/expression/struct.h>*/
/*#include <named/expression/new.h>*/

/*#include <named/zebu_expression/struct.h>*/

/*#include <assertion/new.h>*/
/*#include <assertion/free.h>*/

/*#include <parse/assertion/struct.h>*/

/*#include <set/string/contains.h>*/
/*#include <list/string/pop.h>*/

/*#include <named/type/new.h>*/

/*#include <list/assertion/append.h>*/

/*#include <list/zebu_expression/new.h>*/
/*#include <list/zebu_expression/append.h>*/
/*#include <list/zebu_expression/free.h>*/

/*#include <list/string/foreach.h>*/

/*#include <list/declaration/append.h>*/

/*#include <declaration/new.h>*/
/*#include <declaration/free.h>*/

/*#include <parse/assertion/struct.h>*/

/*#include "unresolved/new.h"*/
/*#include "unresolved/inc.h"*/
/*#include "unresolved/len.h"*/
/*#include "unresolved/discard.h"*/
/*#include "unresolved/resolve.h"*/
/*#include "unresolved/foreach.h"*/
/*#include "unresolved/is_nonempty.h"*/
/*#include "unresolved/free.h"*/

/*#include "resolve_variables.h"*/

/*#include "determine_direct_uses.h"*/

/*#include "build_type.h"*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <assertion/new.h>
#include <assertion/free.h>

/*#include <avl/alloc_tree.h>*/
/*#include <avl/insert.h>*/
#include <avl/foreach.h>

#include <named/type/struct.h>
/*#include <named/type/new.h>*/
/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

#include <parse/assertion/struct.h>

#include <parse/declaration/struct.h>

#include <list/raw_declaration/foreach.h>

#include <type/print.h>
#include <type/struct.h>

#include <value/bool/struct.h>

#include <declaration/new.h>
#include <declaration/free.h>

#include <list/declaration/append.h>

#include <string/struct.h>

/*#include <named/expression/new.h>*/
/*#include <named/expression/compare.h>*/
/*#include <named/expression/free.h>*/

#include <expression/literal/struct.h>
#include <expression/struct.h>
#include <expression/print.h>
#include <expression/free.h>

#include <list/assertion/append.h>

#include <list/raw_assertion/foreach.h>

#include <type_cache/get_type/environment.h>

#include <type_cache/get_type/list.h>

#include "scope/layer.h"
#include "scope/struct.h"
#include "scope/new.h"
#include "scope/push.h"
#include "scope/declare.h"
/*#include "scope/lookup.h"*/
#include "scope/pop.h"
#include "scope/free.h"

#include "specialize/shared.h"
#include "specialize/expression.h"

#include "determine_type/expression.h"

#include "type_check.h"

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types, // named types
	
	struct raw_declaration_list* raw_declarations,
	struct raw_assertion_list* raw_assertions,
	
	struct stringset* grammar_sets,
	struct declaration_list* declarations,
	struct assertion_list* assertions)
{
	ENTER;
	
	struct type_check_scope* scope = new_type_check_scope();
	
	type_check_scope_push(scope);
	
	avl_foreach(grammar_types, ({
		void runme(void* ptr)
		{
			struct named_type* ntype = ptr;
			
			struct type* ltype = type_cache_get_list_type(tcache, ntype->type);
			
			type_check_scope_declare(scope, ntype->name);
			
			type_check_scope_declare_type(scope, ntype->name, ltype);
		}
		runme;
	}));
	
	raw_declaration_list_foreach(raw_declarations, ({
		void runme(struct raw_declaration* raw_declaration)
		{
			struct string* name = raw_declaration->name;
			
			type_check_scope_declare(scope, name);
		}
		runme;
	}));
	
	raw_declaration_list_foreach(raw_declarations, ({
		void runme(struct raw_declaration* raw_declaration)
		{
			struct string* name = raw_declaration->name;
			
			printf("%s: determining type of '%.*s': ", argv0, name->len, name->chars);
			
			struct type* type = determine_type_of_expression(
				raw_declaration->expression, tcache, scope);
			
			#ifdef VERBOSE
			type_print(type), puts("");
			#endif
			
			type_check_scope_declare_type(scope, name, type);
		}
		runme;
	}));
	
	struct type* environment = type_cache_get_environment_type(tcache, NULL, scope->head->tree);
	
	dpv(environment);
	
	struct specialize_shared sshared = {
		.environment = environment,
	};
	
	raw_declaration_list_foreach(raw_declarations, ({
		void runme(struct raw_declaration* raw_declaration)
		{
			struct string* name = raw_declaration->name;
			
			printf("%s: specializing '%.*s' declaration: ", argv0, name->len, name->chars);
			
			struct expression* typed = specialize_expression(
				tcache, &sshared, scope, raw_declaration->expression);
			
			expression_print(typed), puts("");
			
			if (typed->kind == ek_literal)
			{
				struct literal_expression* spef = (void*) typed;
				
				type_check_scope_declare_value(scope, name, spef->value);
			}
			
			struct declaration* declaration = new_declaration(name, typed);
			
			declaration_list_append(declarations, declaration);
			
			free_declaration(declaration);
			
			free_expression(typed);
		}
		runme;
	}));
	
	raw_assertion_list_foreach(raw_assertions, ({
		void runme(struct raw_assertion* raw_assertion)
		{
			printf("%s: specializing assertion: ", argv0);
			
			struct expression* typed = specialize_expression(
				tcache, &sshared, scope, raw_assertion->expression);
			
			expression_print(typed), puts("");
			
			if (typed->type->kind != tk_bool)
			{
				TODO;
				exit(1);
			}
			
			if (typed->kind == ek_literal)
			{
				struct literal_expression* literal = (void*) typed;
				
				struct bool_value* value = (void*) literal->value;
				
				if (!value->value)
				{
					TODO;
				}
			}
			else
			{
				struct assertion* assertion = new_assertion(raw_assertion->kind, typed);
				
				assertion_list_append(assertions, assertion);
				
				free_assertion(assertion);
			}
			
			free_expression(typed);
			
		}
		runme;
	}));
	
	type_check_scope_pop(scope);
	
	free_type_check_scope(scope);
	
	EXIT;
}























