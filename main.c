
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <cmdln/flags.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <parse/driver.h>

#include <parse/assertion/free.h>

#include <assertion/free.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <named/zebu_expression/compare.h>
#include <named/zebu_expression/free.h>

#include <named/zebu_type/compare.h>
#include <named/zebu_type/free.h>

#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <named/structinfo/compare.h>
#include <named/structinfo/free.h>

#include <quack/new.h>
#include <quack/foreach.h>
#include <quack/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <type_cache/new.h>
#include <type_cache/free.h>

#include <type_check/specialize_grammar_types.h>
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
	
	struct type_cache* tcache = new_type_cache();
	
	struct quack* raw_assertions = new_quack();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_named_structinfos, free_named_structinfo);
	struct avl_tree_t* raw_declares = avl_alloc_tree(compare_named_zebu_expressions, free_named_zebu_expression);
	parse_driver(lex, grammar, structinfos, raw_declares, raw_assertions, tcache, flags->input_path);
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	specialize_grammar_types(types, tcache, structinfos);
	
/*	struct quack* typed_assertions = new_quack();*/
/*	struct avl_tree_t* typed_declares = avl_alloc_tree(compare_named_expressions, free_named_expression);*/
	type_check(tcache, types, raw_declares, raw_assertions);
	
	TODO;
	#if 0
	struct yacc_state* start = yacc(lex, structinfos, grammar);
	
	struct stringtree* content = out(
		tcache, types,
		raw_forwards,
		typed_declares,
		typed_assertions,
		start);
	
	FILE* stream = fopen(flags->output_path, "w");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	stringtree_stream(content, stream);
	
	fclose(stream);
	
	quack_foreach(raw_assertions, ({
		void runme(void* ptr) {
			free_raw_assertion(ptr);
		}
		runme;
	}));
	
	quack_foreach(typed_assertions, ({
		void runme(void* ptr) {
			free_assertion(ptr);
		}
		runme;
	}));
	
	avl_free_tree(typed_declares);
	
	free_quack(typed_assertions);
	
	avl_free_tree(raw_declares);
	
	avl_free_tree(structinfos);
	
	free_quack(raw_assertions);
	
	free_stringtree(content);
	
	free_type_cache(tcache);
	
	avl_free_tree(grammar);
	
	free_yacc_state(start);
	
	avl_free_tree(types);
	
	free_cmdln(flags);
	
	free_lex(lex);
	
	EXIT;
	return 0;
	#endif
}















