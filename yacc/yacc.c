
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/foreach.h>
#include <avl/free_tree.h>

/*#include <string/new.h>*/
#include <string/struct.h>
#include <string/inc.h>
#include <string/are_equal.h>
#include <string/compare.h>
#include <string/free.h>

#include <quack/new.h>
#include <quack/pop.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include <named/trie/compare.h>
#include <named/trie/free.h>

#include <named/grammar/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>
#include <set/unsigned/foreach.h>
#include <set/unsigned/update.h>
#include <set/unsigned/clone.h>
#include <set/unsigned/head.h>

#include <set/unsignedset/foreach.h>
#include <set/unsignedset/free.h>

#include <misc/escape.h>

#include <lex/struct.h>
#include <lex/build_tokenizer/build_tokenizer.h>
#include <lex/find_shortest_accepting.h>

#include <named/structinfo/struct.h>

#include <named/trie/struct.h>

#include <list/statement/foreach.h>

#include <statement/struct.h>
#include <statement/parse/struct.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "trie/struct.h"

#include "stateinfo/new.h"
#include "stateinfo/add.h"
#include "stateinfo/compare.h"
#include "stateinfo/inc.h"
#include "stateinfo/free.h"
#include "stateinfo/foreach.h"

#include "structinfo/free.h"

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_reduce_transition.h"
#include "state/add_grammar_transition.h"

#include "build_tries.h"
#include "expand_stateinfo.h"
#include "calc_firsts.h"
#include "yacc.h"

struct unsignedset;
struct trie;
struct lex_state;

struct mapping
{
	struct stateinfo* stateinfo;
	struct yacc_state* state;
	
	// unsigned hopcount;
	// struct mapping* prev;
};

static struct mapping* new_mapping(
	struct stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateinfo = inc_stateinfo(stateinfo);
	this->state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_stateinfo(A->stateinfo, B->stateinfo);
}

static void free_mapping(void* ptr)
{
	ENTER;
	
	struct mapping* this = ptr;
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

struct shift_node
{
	unsigned token; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

struct reduce_node
{
	unsigned token; // must be the first
	
	struct string* reduce_as;
	
	struct string* grammar;
	
	struct reductioninfo* reductioninfo;
	
	struct structinfo* structinfo;
};

struct subgrammar_node
{
	struct string* grammar; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

static struct shift_node* new_shift_node(
	unsigned token)
{
	ENTER;
	
	struct shift_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_shift_nodes(const void* a, const void* b)
{
	const struct shift_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return 0;
}

static void free_shift_node(void* ptr)
{
	struct shift_node* const this = ptr;
	ENTER;
	
	free_stateinfo(this->stateinfo);
	free(this);
	
	EXIT;
}

static struct reduce_node* new_reduce_node(
	unsigned token,
	struct string* reduce_as,
	struct string* grammar,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	assert(grammar);
	
	struct reduce_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->reduce_as = inc_string(reduce_as);
	
	this->grammar = inc_string(grammar);
	
	this->reductioninfo = reductioninfo;
	
	this->structinfo = structinfo;
	
	EXIT;
	return this;
}

static int compare_reduce_nodes(const void* a, const void* b)
{
	const struct reduce_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return +0;
}

static void free_reduce_node(void* ptr)
{
	ENTER;
	
	struct reduce_node* node = ptr;
	
	free_string(node->reduce_as);
	
	free_string(node->grammar);
	
	free(node);
	
	EXIT;
}

static struct subgrammar_node* new_subgrammar_node(struct string* grammar)
{
	ENTER;
	
	struct subgrammar_node* this = smalloc(sizeof(*this));
	
	this->grammar = inc_string(grammar);
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_subgrammar_nodes(const void* a, const void* b)
{
	const struct subgrammar_node* A = a, *B = b;
	
	return compare_strings(A->grammar, B->grammar);
}

static void free_subgrammar_node(void* ptr)
{
	struct subgrammar_node* const this = ptr;
	ENTER;
	
	free_string(this->grammar);
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

static void add_shift(
	struct avl_tree_t* shift_tokens,
	unsigned token,
	struct trie* to,
	struct unsignedset* tokens)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(shift_tokens, &(struct shift_node) {token});
	
	struct unsignedset* tokens_dup = unsignedset_clone(tokens);
	
	if (node)
	{
		struct shift_node* old = node->item;
		
		stateinfo_add(old->stateinfo, to, tokens_dup);
	}
	else
	{
		struct shift_node* new = new_shift_node(token);
		
		stateinfo_add(new->stateinfo, to, tokens_dup);
		
		avl_insert(shift_tokens, new);
	}
	
	free_unsignedset(tokens_dup);
	
	EXIT;
}

static void add_reduce(
	struct avl_tree_t* reduce_tokens,
	unsigned token,
	struct string* reduce_as,
	struct string* grammar,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(reduce_tokens, &(struct reduce_node) {token});
	
	if (node)
	{
		struct reduce_node* old = node->item;
		
		struct string* a, *b;
		
		if (compare_strings(old->reduce_as, reduce_as) < 0)
		  a = old->reduce_as, b = reduce_as;
		else
		  a = reduce_as, b = old->reduce_as;
		
	  fprintf(stderr, "guardian: reduce/reduce error between grammar "
	    "rule %.*s and %.*s!\n", a->len, a->chars, b->len, b->chars);
    
		exit(e_reduce_reduce_error);
	}
	else
	{
		struct reduce_node* new = new_reduce_node(token, reduce_as, grammar, reductioninfo, structinfo);
		
		avl_insert(reduce_tokens, new);
	}
	
	EXIT;
}


static void add_subgrammar(
	struct avl_tree_t* subgrammars,
	struct string* grammar,
	struct trie* to,
	struct unsignedset* tokens)
{
	ENTER;
	
	dpvs(grammar);
	
	struct avl_node_t* node = avl_search(subgrammars, &grammar);
	
	struct unsignedset* tokens_dup = unsignedset_clone(tokens);
	
	if (node)
	{
		struct subgrammar_node* old = node->item;
		
		stateinfo_add(old->stateinfo, to, tokens_dup);
	}
	else
	{
		struct subgrammar_node* new = new_subgrammar_node(grammar);
		
		stateinfo_add(new->stateinfo, to, tokens_dup);
		
		avl_insert(subgrammars, new);
	}
	
	free_unsignedset(tokens_dup);
	
	EXIT;
}

static void shift_reduce_error(
	struct lex_state* start,
	struct unsignedset* tokenset)
{
	ENTER;
	
	unsigned char* string = lex_find_shortest_accepting(start, tokenset);
	
	char* escaped = escape(string);
	
	fprintf(stderr, "guardian: shift/reduce error on token %s\n", escaped);
	
	free(escaped), free(string);
	
	EXIT;
	exit(e_shift_reduce_error);
}

void yacc(
	struct lex* lex,
	struct avl_tree_t* structinfos,
	struct avl_tree_t* grammar,
	struct statement_list* statements)
{
	ENTER;
	
	#ifdef VERBOSE
	void handler1(int _)
	{
		char buffer[1000] = {};
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "guardian: generating parser ...\r");
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	struct avl_tree_t* named_tries = avl_alloc_tree(compare_named_tries, free_named_trie);
	
	avl_foreach(grammar, ({
		void runme(void* ptr)
		{
			struct named_grammar* grammar_rule = ptr;
			
			struct string* name = grammar_rule->name;
			
			dpvs(name);
			
			struct avl_node_t* node = avl_search(structinfos, &name);
			
			assert(node);
			
			struct named_structinfo* nstructinfo = node->item;
			
			build_tries(named_tries, name, grammar_rule->grammar, nstructinfo->structinfo);
		}
		runme;
	}));
	
	struct avl_tree_t* named_firsts = calc_firsts(named_tries);
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	statement_list_foreach(statements, ({
		void runme(struct statement* statement)
		{
			if (statement->kind == sk_parse)
			{
				struct parse_statement* pstatement = (void*) statement;
				
				struct stateinfo* stateinfo = new_stateinfo();
				
				struct avl_node_t* node = avl_search(named_tries, &pstatement->grammar_name);
				
				assert(node);
				
				struct named_trie* start_trie = node->item;
				
				dpv(start_trie);
				
				struct unsignedset* lookahead_tokens = new_unsignedset();
				
				unsignedset_add(lookahead_tokens, lex->EOF_token_id);
				
				stateinfo_add(stateinfo, start_trie->trie, lookahead_tokens);
				
				expand_stateinfo(stateinfo, named_tries, named_firsts);
				
				struct yacc_state* state = new_yacc_state();
				
				struct mapping* mapping = new_mapping(stateinfo, state);
				
				pstatement->ystate = state;
				
				avl_insert(mappings, mapping);
				
				quack_append(todo, mapping);
				
				free_unsignedset(lookahead_tokens);
				
				free_stateinfo(stateinfo);
			}
		}
		runme;
	}));
	
	while (quack_is_nonempty(todo))
	{
		struct mapping* const mapping = quack_pop(todo);
		
		struct stateinfo* const stateinfo = mapping->stateinfo;
		
		struct yacc_state* const state = mapping->state;
		
		struct unsignedset* all_tokens = new_unsignedset();
		
		struct avl_tree_t* shift_tokens = avl_alloc_tree(compare_shift_nodes, free_shift_node);
		
		struct avl_tree_t* reduce_tokens = avl_alloc_tree(compare_reduce_nodes, free_reduce_node);
		
		struct avl_tree_t* subgrammars = avl_alloc_tree(compare_subgrammar_nodes, free_subgrammar_node);
		
		stateinfo_foreach(stateinfo, ({
			void runme(struct trie* trie, struct unsignedset* tokens)
			{
				ENTER;
				
				if (trie->reduce_as)
				{
					assert(trie->grammar);
					
					unsignedset_foreach(tokens, ({
						void runme(unsigned token) {
							add_reduce(reduce_tokens, token, trie->reduce_as, trie->grammar, trie->reductioninfo, trie->structinfo);
						}
						runme;
					}));
					
					unsignedset_update(all_tokens, tokens);
				}
				
				for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
				{
					const struct trie_transition* const ele = trie->transitions.data[i];
					
					add_shift(shift_tokens, ele->token, ele->to, tokens);
					
					unsignedset_add(all_tokens, ele->token);
				}
				
				for (unsigned i = 0, n = trie->grammars.n; i < n; i++)
				{
					const struct trie_grammar_transition* ele = trie->grammars.data[i];
					
					dpvs(ele->grammar);
					
					add_subgrammar(subgrammars, ele->grammar, ele->to, tokens);
				}
				
				EXIT;
			}
			runme;
		}));
		
		struct lex_state* tokenizer_start;
		
		// don't free 'tokens', lex will do that
		struct unsignedsetset* tokens = lex_build_tokenzer(
			/* (in/out) struct lex* lex:            */ lex,
			/* (   out) struct lex_state* start:    */ &tokenizer_start,
			/* (in)     struct unsignedset* tokens: */ all_tokens);
		
		state->tokenizer_start = tokenizer_start;
		
		unsignedsetset_foreach(tokens, ({
			void runme(struct unsignedset* ele)
			{
				ENTER;
				
				unsigned first = unsignedset_head(ele);
				
				dpv(first);
				
				// is this a shift or a reduce transition?
				if (avl_search(shift_tokens, &(struct shift_node) {first}))
				{
					struct stateinfo* subinfo = new_stateinfo();
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token)
						{
							dpv(token);
							
							if (avl_search(reduce_tokens, &(struct reduce_node){token}))
							{
								shift_reduce_error(tokenizer_start, ele);
							}
							
							struct shift_node* shift = avl_search(shift_tokens, &(struct shift_node) {token})->item;
							
							stateinfo_foreach(shift->stateinfo, ({
								void runme(struct trie* subtrie, struct unsignedset* subtokens) {
									struct unsignedset* dup2 = unsignedset_clone(subtokens);
									stateinfo_add(subinfo, subtrie, dup2);
									free_unsignedset(dup2);
								}
								runme;
							}));
						}
						runme;
					}));
					
					expand_stateinfo(subinfo, named_tries, named_firsts);
					
					struct avl_node_t* node = avl_search(mappings, &subinfo);
					
					if (node)
					{
						struct mapping* submapping = node->item;
						
						yacc_state_add_transition(state, ele, submapping->state);
					}
					else
					{
						struct yacc_state* substate = new_yacc_state();
						
						struct mapping* submapping = new_mapping(subinfo, substate);
						
						yacc_state_add_transition(state, ele, substate);
						
						avl_insert(mappings, submapping);
						
						quack_append(todo, submapping);
					}
					
					free_stateinfo(subinfo);
				}
				else if (avl_search(reduce_tokens, &first))
				{
					struct string* reduce_as = NULL;
					struct string* grammar = NULL;
					struct reductioninfo* reductioninfo;
					struct structinfo* structinfo;
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token) {
							dpv(token);
							
							if (avl_search(shift_tokens, &(struct reduce_node) {token}))
							{
								shift_reduce_error(tokenizer_start, ele);
							}
							
							struct avl_node_t* node = avl_search(reduce_tokens, &first);
							
							assert(node);
							
							struct reduce_node* reduce = node->item;
							
							dpvs(reduce->reduce_as);
							
							if (!reduce_as)
							{
								reduce_as = reduce->reduce_as;
								grammar = reduce->grammar;
								reductioninfo = reduce->reductioninfo;
								structinfo = reduce->structinfo;
							}
							else if (!strings_are_equal(reduce_as, reduce->reduce_as))
							{
								TODO;
							}
						}
						runme;
					}));
					
					yacc_state_add_reduce_transition(state, ele, reduce_as, grammar, reductioninfo, structinfo);
				}
				else
				{
					// huh?
					TODO;
				}
				
				EXIT;
			}
			runme;
		}));
		
		avl_foreach(subgrammars, ({
			void runme(void* ptr)
			{
				struct subgrammar_node* const ele = ptr;
				
				dpvs(ele->grammar);
				
				struct stateinfo* subinfo = new_stateinfo();
				
				stateinfo_foreach(ele->stateinfo, ({
					void runme(struct trie* subtrie, struct unsignedset* subtokens)
					{
						struct unsignedset* dup2 = unsignedset_clone(subtokens);
						stateinfo_add(subinfo, subtrie, dup2);
						free_unsignedset(dup2);
					}
					runme;
				}));
				
				expand_stateinfo(subinfo, named_tries, named_firsts);
				
				struct avl_node_t* node = avl_search(mappings, &subinfo);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					yacc_state_add_grammar_transition(state, ele->grammar, submapping->state);
				}
				else
				{
					struct yacc_state* substate = new_yacc_state();
					
					struct mapping* submapping = new_mapping(subinfo, substate);
					
					yacc_state_add_grammar_transition(state, ele->grammar, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
				
				free_stateinfo(subinfo);
			}
			runme;
		}));
		
		free_unsignedsetset(tokens);
		
		avl_free_tree(shift_tokens);
		
		avl_free_tree(reduce_tokens);
		
		avl_free_tree(subgrammars);
		
		free_unsignedset(all_tokens);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	avl_free_tree(named_firsts);
	
	avl_free_tree(named_tries);
	
	EXIT;
}
















