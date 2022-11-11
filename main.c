
/*#include <parse/assertion/free.h>*/

/*#include <assertion/free.h>*/

/*#include <named/zebu_expression/compare.h>*/
/*#include <named/zebu_expression/free.h>*/

/*#include <named/zebu_type/compare.h>*/
/*#include <named/zebu_type/free.h>*/

/*#include <named/expression/compare.h>*/
/*#include <named/expression/free.h>*/

/*#include <quack/new.h>*/
/*#include <quack/foreach.h>*/
/*#include <quack/free.h>*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <cmdln/flags.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/structinfo/compare.h>
#include <named/structinfo/free.h>

#include <list/raw_declaration/new.h>
#include <list/raw_declaration/free.h>

#include <list/raw_assertion/new.h>
#include <list/raw_assertion/free.h>

#include <parse/driver.h>

#include <type_cache/new.h>
#include <type_cache/free.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <type_check/specialize_grammar_types.h>

#include <set/string/new.h>
#include <set/string/free.h>

#include <list/declaration/new.h>
#include <list/declaration/free.h>

#include <list/assertion/new.h>
#include <list/assertion/free.h>

#include <type_check/type_check.h>

#include <yacc/yacc.h>

#include <yacc/state/free.h>

#include <out/out.h>

#include <stringtree/stream.h>
#include <stringtree/free.h>

int main(int argc, char* const* argv)
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct lex* lex = new_lex();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_named_structinfos, free_named_structinfo);
	
	struct raw_declaration_list* raw_declarations = new_raw_declaration_list();
	
	struct raw_assertion_list* raw_assertions = new_raw_assertion_list();
	
	parse_driver(lex, grammar, structinfos, raw_declarations, raw_assertions, flags->input_path);
	
	struct type_cache* tcache = new_type_cache();
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	specialize_grammar_types(types, tcache, structinfos);
	
	struct stringset* grammar_sets = new_stringset();
	
	struct declaration_list* declarations = new_declaration_list();
	
	struct assertion_list* assertions = new_assertion_list();
	
	type_check(
		tcache, types, grammar_sets,
		raw_declarations, raw_assertions,
		declarations, assertions);
	
	struct yacc_state* start = yacc(lex, structinfos, grammar);
	
	struct stringtree* content = out(tcache, types, grammar_sets, declarations, assertions, start);
	
	FILE* stream = fopen(flags->output_path, "w");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	stringtree_stream(content, stream);
	
	free_stringtree(content);
	
	fclose(stream);
	
	free_raw_declaration_list(raw_declarations);
	
	free_raw_assertion_list(raw_assertions);
	
	free_declaration_list(declarations);
	
	free_assertion_list(assertions);
	
	avl_free_tree(structinfos);
	
	free_type_cache(tcache);
	
	avl_free_tree(grammar);
	
	free_yacc_state(start);
	
	free_stringset(grammar_sets);
	
	avl_free_tree(types);
	
	free_cmdln(flags);
	
	free_lex(lex);
	
	EXIT;
	
	#ifdef DEBUGGING
	if (debug_depth)
	{
		fflush(stdout);
		assert(0);
	}
	#endif
	return 0;
}















