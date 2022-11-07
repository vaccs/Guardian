
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <type_cache/get_type/grammar.h>
#include <type_cache/get_type/int.h>
#include <type_cache/get_type/char.h>
#include <type_cache/get_type/charlist.h>

#include <parse/parse.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>
#include <out/function_queue/submit_append.h>

/*#include <yacc/structinfo/struct.h>*/
#include <yacc/structinfo/foreach.h>
#include <yacc/structinfo/node/struct.h>

#include "struct.h"
#include "print_source.h"

void reductioninfo_print_source(
	struct stringtree* tree,
	struct reductioninfo* this,
	struct structinfo* structinfo,
	struct out_shared* shared,
	const char* grammar)
{
	ENTER;
	
	switch (this->kind)
	{
		case rik_token:
		{
			stringtree_append_printf(tree, ""
				"{" "\n"
					"struct token* token = data.data[--yacc.n, --data.n];" "\n"
			"");
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct structinfo_node* node)
				{
					struct string* name = node->name;
					
					dpvs(name);
					
					switch (node->type)
					{
						case snt_token_scalar:
						{
							if (!node->tokentype)
							{
								struct type* stype = type_cache_get_charlist_type(shared->tcache);
								struct type* ctype = type_cache_get_char_type(shared->tcache);
								
								unsigned new_string_id = function_queue_submit_new(shared->fqueue, stype);
								unsigned new_char_id = function_queue_submit_new(shared->fqueue, ctype);
								
								unsigned append_id = function_queue_submit_append(shared->fqueue, stype);
								
								unsigned free_char_id = function_queue_submit_free(shared->fqueue, ctype);
								
								stringtree_append_printf(tree, ""
									"{"
										"struct type_%u* string = func_%u();"
										"for (unsigned i = 0, n = token->len; i < n; i++)"
										"{"
											"struct type_%u* character = func_%u(token->data[i]);"
											"func_%u(string, character);"
											"func_%u(character);"
										"}"
										"value->$%.*s = string;"
									"}"
								"", stype->id, new_string_id,
								ctype->id, new_char_id,
								append_id,
								free_char_id,
								name->len, name->chars);
							}
							else if (node->tokentype->char_)
							{
								TODO;
							}
							else if (node->tokentype->int_)
							{
								struct type* type = type_cache_get_int_type(shared->tcache);
								
								unsigned new_id = function_queue_submit_new(shared->fqueue, type);
								
								stringtree_append_printf(tree, ""
									"{"
										"struct type_%u* integer = func_%u();"
										"if (mpz_set_str(integer->value, (char*) token->data, 10) < 0)"
										"{"
											"assert(!\"TODO: mpz_set_str(): failed!\");"
										"}"
										"value->$%.*s = integer;"
									"}"
								"", type->id, new_id, name->len, name->chars);
							}
							else if (node->tokentype->float_)
							{
								TODO;
							}
							else
							{
								TODO;
							}
							break;
						}
						
						case snt_token_array:
						{
							TODO;
							#if 0
							fprintf(stream, ""
								"\t" "\t" "if (value->%s.n == value->%s.cap)" "\n"
								"\t" "\t" "{" "\n"
								"\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "}" "\n"
								"\t" "\t" "memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "value->%s.data[0] = inc_%s_token(token), value->%s.n++;" "\n"
							"", name, name,
							name, name,
							name, name, name, name,
							name, name, name, name,
							name, prefix, name);
							#endif
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			stringtree_append_printf(tree, ""
					"free_token(token);" "\n"
				"}" "\n"
			"");
			break;
		}
		
		case rik_grammar:
		{
			struct type* type = type_cache_get_grammar_type(shared->tcache, this->grammar);
			
			stringtree_append_printf(tree, ""
				"{"
					"struct type_%u* subgrammar = data.data[--yacc.n, --data.n];"
			"", type->id);
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct structinfo_node* node)
				{
					TODO;
					#if 0
					const char* name = node->name->chars;
					
					switch (node->type)
					{
						case snt_grammar_scalar:
						{
							fprintf(stream, ""
								"\t" "\t" "free_%s_%s(value->%s), value->%s = inc_%s_%s(subgrammar);" "\n"
							"", prefix, type, name, name, prefix, type);
							break;
						}
						
						case snt_grammar_array:
						{
							fprintf(stream, ""
								"\t" "\t" "if (value->%s.n == value->%s.cap)" "\n"
								"\t" "\t" "{" "\n"
								"\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "}" "\n"
								"\t" "\t" "memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "value->%s.data[0] = inc_%s_%s(subgrammar), value->%s.n++;" "\n"
							"", name, name,
							name, name,
							name, name, name, name,
							name, name, name, name,
							name, prefix, type, name);
							break;
						}
						
						default:
							TODO;
							break;
					}
					#endif
				}
				runme;
			}));
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, type);
			
			stringtree_append_printf(tree, ""
					"func_%u(subgrammar);"
				"}"
			"", free_id);
			break;
		}
		
		case rik_trie:
		{
			TODO;
			#if 0
			dpvs(this->grammar);
			
			assert(this->grammar);
			
			fprintf(stream, ""
				"\t" "\t" "{" "\n"
				"\t" "\t" "\t" "struct %s_%s* trie = data.data[--yacc.n, --data.n];" "\n"
			"", prefix, grammar);
			
			structinfo_foreach(structinfo, ({
				void runme(struct structinfo_node* node)
				{
					const char* const name = node->name->chars;
					
					switch (node->type)
					{
						case snt_token_scalar:
						{
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s) { free_%s_token(value->%s); value->%s = inc_%s_token(trie->%s); }" "\n"
							"", name, prefix, name, name, prefix, name);
							break;
						}
						
						case snt_token_array:
						{
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s.n)"
								"\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
								"\t" "\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "\t" "\t" "}" "\n"
								"\t" "\t" "\t" "\t" "memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "\t" "\t" "for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data[i] = inc_%s_token(trie->%s.data[i]);" "\n"
								"\t" "\t" "\t" "\t" "value->%s.n += trie->%s.n;" "\n"
								"\t" "\t" "\t" "}" "\n"
							"", name,
							name, name, name,
							name, name,
							name, name, name, name,
							name, name, name, name, name,
							name,
							name, prefix, name,
							name, name);
							break;
						}
						
						case snt_grammar_scalar:
						{
							const char* const type = node->grammar.name->chars;
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s) { free_%s_%s(value->%s); value->%s = inc_%s_%s(trie->%s); }" "\n"
							"", name, prefix, type, name, name, prefix, type, name);
							break;
						}
						
						case snt_grammar_array:
						{
							const char* const type = node->grammar.name->chars;
							
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s.n)" "\n"
								"\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
								"\t" "\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "\t" "\t" "}" "\n"
								"\t" "\t" "\t" "\t" "memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "\t" "\t" "for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data[i] = inc_%s_%s(trie->%s.data[i]);" "\n"
								"\t" "\t" "\t" "\t" "value->%s.n += trie->%s.n;" "\n"
								"\t" "\t" "\t" "}" "\n"
							"", name,
							name, name, name,
							name, name,
							name, name, name, name,
							name, name, name, name, name,
							name,
							name, prefix, type, name,
							name, name);
							break;
						}
						
						case snt_scanf_scalar:
						{
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s) { value->%s = trie->%s; }" "\n"
							"", name, name, name);
							break;
						}
						
						case snt_scanf_array:
						{
							TODO;
							break;
						}
						
						case snt_user_defined:
							break;
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			fprintf(stream, ""
				"\t" "\t" "\t" "free_%s_%s(trie);" "\n"
				"\t" "\t" "}" "\n"
			"", prefix, grammar);
			#endif
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(tree, this->prev, structinfo, shared, grammar);
	}
	
	EXIT;
}


