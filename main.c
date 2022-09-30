
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

#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <set/ptr/new.h>

#include <lex/new.h>
#include <lex/free.h>

#include <type_cache/new.h>
#include <type_cache/free.h>

#include <type_check/type_check.h>

#include <yacc/yacc.h>

#include <yacc/state/free.h>

#include <out/out.h>

#include <stringtree/stream.h>
#include <stringtree/free.h>

int main(int argc, char* const* argv)
{
	#ifdef DEBUGGING
/*	setvbuf(stdout, NULL, 0, _IONBF);*/
/*	setvbuf(stderr, NULL, 0, _IONBF);*/
	#endif
	
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct lex* lex = new_lex();
	
	struct type_cache* tcache = new_type_cache();
	
	struct ptrset* raw_assertions = new_ptrset();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	struct avl_tree_t* raw_declares = avl_alloc_tree(compare_named_zebu_expressions, free_named_zebu_expression);
	
	parse_driver(lex, grammar, types, raw_declares, raw_assertions, tcache, flags->input_path);
	
	struct ptrset* typed_assertions = new_ptrset();
	
	struct avl_tree_t* typed_declares = avl_alloc_tree(compare_named_expressions, free_named_expression);
	
	type_check(tcache, types, typed_declares, typed_assertions, raw_declares, raw_assertions);
	
	struct yacc_state* start = yacc(lex, grammar);
	
	struct stringtree* content = out();
	
	stringtree_stream(content, stdout);
	
	free_stringtree(content);
	
	ptrset_foreach(raw_assertions, ({
		void runme(void* ptr) {
			free_raw_assertion(ptr);
		}
		runme;
	}));
	
	ptrset_foreach(typed_assertions, ({
		void runme(void* ptr) {
			free_assertion(ptr);
		}
		runme;
	}));
	
	free_yacc_state(start);
	
	free_ptrset(raw_assertions);
	
	free_ptrset(typed_assertions);
	
	avl_free_tree(typed_declares);
	
	avl_free_tree(raw_declares);
	
	free_type_cache(tcache);
	
	avl_free_tree(grammar);
	
	avl_free_tree(types);
	
	free_cmdln(flags);
	
	free_lex(lex);
	
	EXIT;
	return 0;
}















