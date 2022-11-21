
#include <assert.h>

#include <stdlib.h>
#include <debug.h>

#include <avl/insert.h>

#include <string/new.h>
#include <string/free.h>

#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/combine_structinfos.h>
#include <gegex/free.h>

#include <named/grammar/new.h>

#include <named/structinfo/new.h>

#include <yacc/structinfo/free.h>

#include <list/raw_statement/append.h>

#include "parse.h"
#include "raw_statement/new.h"
#include "raw_statement/free.h"
#include "grammar/3.root.h"
#include "process_parse.h"

static unsigned counter = 0;

void process_parse(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct raw_statement_list* statements,
	struct zebu_parse_statement* zstatement)
{
	ENTER;
	
	struct gbundle nfa = read_grammar_root(lex, zstatement->grammar);
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	struct string* name = new_string_from_format("$start%u", counter++);
	
	if (!avl_insert(grammar, new_named_grammar(name, simp)))
	{
		TODO;
		exit(1);
	}
	
	struct structinfo* structinfo = gegex_combine_structinfos(simp);
	
	if (!avl_insert(types, new_named_structinfo(name, structinfo)))
	{
		TODO;
		exit(1);
	}
	
	struct raw_statement* statement = new_raw_parse(
		zstatement->parse->line, zstatement->expression, name, simp);
	
	raw_statement_list_append(statements, statement);
	
	free_raw_statement(statement);
	
	free_structinfo(structinfo);
	
	free_gegex(nfa.start);
	
	free_string(name);
	
	free_gegex(dfa);
	
	EXIT;
}





























