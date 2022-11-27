
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <cmdln/flags.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/minimize_lexer.h>
#include <lex/free.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/structinfo/compare.h>
#include <named/structinfo/free.h>

#include <list/raw_statement/new.h>
#include <list/raw_statement/free.h>

#include <list/statement/new.h>
#include <list/statement/free.h>

#include <parse/driver.h>

#include <type_cache/new.h>
#include <type_cache/free.h>
#include <type_check/specialize_grammar_types.h>
#include <type_check/type_check.h>

#include <named/type/compare.h>
#include <named/type/free.h>

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
	
	struct raw_statement_list* raw_statements = new_raw_statement_list();
	
	parse_driver(lex, grammar, structinfos, raw_statements, flags->input_path);
	
	
	struct type_cache* tcache = new_type_cache();
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	specialize_grammar_types(types, tcache, structinfos);
	
	
	struct statement_list* statements = new_statement_list();
	
	type_check(tcache, types, raw_statements, statements);
	
	
	yacc(lex, structinfos, grammar, statements);
	
	
	if (flags->minimize_lexer)
	{
		lex_minimize_lexer(lex, statements);
	}
	
	
	struct stringtree* content = out(tcache, types, statements);
	
	FILE* stream = fopen(flags->output_path, "w");
	
	if (!stream)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, flags->output_path);
		exit(1);
	}
	
	stringtree_stream(content, stream);
	
	
	free_raw_statement_list(raw_statements);
	
	free_all_yacc_states(statements);
	
	free_statement_list(statements);
	
	avl_free_tree(structinfos);
	
	free_stringtree(content);
	
	free_type_cache(tcache);
	
	avl_free_tree(grammar);
	
	avl_free_tree(types);
	
	free_cmdln(flags);
	
	fclose(stream);
	
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















