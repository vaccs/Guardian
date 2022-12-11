
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <type_cache/get_grammar_type.h>
#include <type_cache/get_int_type.h>
#include <type_cache/get_bool_type.h>
#include <type_cache/get_string_type.h>
#include <type_cache/get_float_type.h>
#include <type_cache/get_list_type.h>

#include <parse/parse.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
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
	struct string* grammar)
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
								struct type* stype = type_cache_get_string_type(shared->tcache);
								
								unsigned new_string_id = function_queue_submit_new(shared->fqueue, stype);
								
								stringtree_append_printf(tree, ""
									"{"
										"unsigned char* chars = malloc(token->len);"
										"for (unsigned i = 0, n = token->len; i < n; i++)"
											"chars[i] = token->data[i];"
										"struct type_%u* string = func_%u(chars, token->len);"
										"value->$%.*s = string;"
									"}"
								"",
								stype->id, new_string_id,
								name->len, name->chars);
							}
							else if (node->tokentype->bool_)
							{
								struct type* type = type_cache_get_bool_type(shared->tcache);
								
								unsigned new_id = function_queue_submit_new(shared->fqueue, type);
								
								stringtree_append_printf(tree, ""
									"{"
										"if (token->len == 4 && !memcmp(token->data, \"true\", 4))"
										"{"
											"value->$%.*s = func_%u(true);"
										"}"
										"else if (token->len == 5 && !memcmp(token->data, \"false\", 5))"
										"{"
											"value->$%.*s = func_%u(false);"
										"}"
										"else"
										"{"
											"assert(!\"TODO: bad boolean input\");"
										"}"
									"}"
								"",
								name->len, name->chars, new_id,
								name->len, name->chars, new_id);
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
								struct type* type = type_cache_get_float_type(shared->tcache);
								
								unsigned new_id = function_queue_submit_new(shared->fqueue, type);
								
								stringtree_append_printf(tree, ""
									"{"
										"errno = 0;"
										"char* m;"
										"__float128 number = strtoflt128((char*) token->data, &m);"
										"if (errno || *m) {"
											"assert(!\"TODO: bad float input\");"
											"exit(1);"
										"}"
										"value->$%.*s = func_%u(number);"
									"}"
								"", name->len, name->chars, new_id);
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
								"if (value->%s.n == value->%s->cap)" "\n"
								"{" "\n"
								"value->%s->cap = value->%s->cap << 1 ?: 1;" "\n"
								"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s->cap);" "\n"
								"}" "\n"
								"memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"value->%s.data[0] = inc_%s_token(token), value->%s.n++;" "\n"
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
					struct string* name = node->name;
					
					switch (node->type)
					{
						case snt_grammar_scalar:
						{
							unsigned inc_id = function_queue_submit_inc(shared->fqueue, type);
							
							unsigned free_id = function_queue_submit_free(shared->fqueue, type);
							
							stringtree_append_printf(tree, ""
								"func_%u(value->$%.*s), value->$%.*s = func_%u(subgrammar);"
							"", free_id, name->len, name->chars, name->len, name->chars, inc_id);
							break;
						}
						
						case snt_grammar_array:
						{
							unsigned inc_id = function_queue_submit_inc(shared->fqueue, type);
							
							struct type* list = type_cache_get_list_type(shared->tcache, type);
							
							unsigned new_id = function_queue_submit_new(shared->fqueue, list);
							
							unsigned append_id = function_queue_submit_append(shared->fqueue, list);
							
							#define N name->len, name->chars
							stringtree_append_printf(tree, "if (value->$%.*s)", N);
							stringtree_append_printf(tree, "{");
							stringtree_append_printf(tree, "	if (value->$%.*s->n == value->$%.*s->cap)", N, N);
							stringtree_append_printf(tree, "	{");
							stringtree_append_printf(tree, "		value->$%.*s->cap = value->$%.*s->cap << 1 ?: 1;", N, N);
							stringtree_append_printf(tree, "		value->$%.*s->data = realloc(value->$%.*s->data, sizeof(*value->$%.*s->data) * value->$%.*s->cap);", N, N, N, N);
							stringtree_append_printf(tree, "	}");
							stringtree_append_printf(tree, "	memmove(value->$%.*s->data + 1, value->$%.*s->data, sizeof(*value->$%.*s->data) * value->$%.*s->n);", N, N, N, N);
							stringtree_append_printf(tree, "	value->$%.*s->data[0] = func_%u(subgrammar), value->$%.*s->n++;", N, inc_id, N);
							stringtree_append_printf(tree, "}");
							stringtree_append_printf(tree, "else");
							stringtree_append_printf(tree, "{");
							stringtree_append_printf(tree, "	value->$%.*s = func_%u();", N, new_id);
							stringtree_append_printf(tree, "	func_%u(value->$%.*s, subgrammar);", append_id, N);
							stringtree_append_printf(tree, "}");
							#undef N
							break;
						}
						
						default:
							TODO;
							break;
					}
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
			dpvs(this->grammar);
			assert(this->grammar);
			
			struct type* type = type_cache_get_grammar_type(shared->tcache, grammar);
			
			stringtree_append_printf(tree, ""
				"{" "\n"
				"struct type_%u* trie = data.data[--yacc.n, --data.n];"
			"", type->id);
			
			structinfo_foreach(structinfo, ({
				void runme(struct structinfo_node* node)
				{
					struct string* name = node->name;
					
					switch (node->type)
					{
						case snt_token_scalar:
						{
							TODO;
							#if 0
							fprintf(stream, ""
								"if (trie->%s) { free_%s_token(value->%s); value->%s = inc_%s_token(trie->%s); }" "\n"
							"", name, prefix, name, name, prefix, name);
							#endif
							break;
						}
						
						case snt_token_array:
						{
							TODO;
							#if 0
							fprintf(stream, ""
								"if (trie->%s.n)"
								"{" "\n"
								"while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
								"{" "\n"
								"value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"}" "\n"
								"memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
								"value->%s.data[i] = inc_%s_token(trie->%s.data[i]);" "\n"
								"value->%s.n += trie->%s.n;" "\n"
								"}" "\n"
							"", name,
							name, name, name,
							name, name,
							name, name, name, name,
							name, name, name, name, name,
							name,
							name, prefix, name,
							name, name);
							#endif
							break;
						}
						
						case snt_grammar_scalar:
						{
							struct type* scalar = type_cache_get_grammar_type(shared->tcache, node->grammar);
							
							unsigned inc_id = function_queue_submit_inc(shared->fqueue, scalar);
							
							unsigned free_id = function_queue_submit_free(shared->fqueue, scalar);
							
							stringtree_append_printf(tree, "if (trie->$%.*s)", name->len, name->chars);
							stringtree_append_printf(tree, "{");
							stringtree_append_printf(tree, "	func_%u(value->$%.*s); ", free_id, name->len, name->chars);
							stringtree_append_printf(tree, "	value->$%.*s = func_%u(trie->$%.*s); ", name->len, name->chars, inc_id, name->len, name->chars);
							stringtree_append_printf(tree, "}");
							break;
						}
						
						case snt_grammar_array:
						{
							struct type* element = type_cache_get_grammar_type(shared->tcache, node->grammar);
							
							struct type* list = type_cache_get_list_type(shared->tcache, element);
							
							unsigned inc_id = function_queue_submit_inc(shared->fqueue, element);
							
							unsigned inc_array_id = function_queue_submit_inc(shared->fqueue, list);
							
							#define N name->len, name->chars
							stringtree_append_printf(tree, "if (trie->$%.*s)", N);
							stringtree_append_printf(tree, "{");
							stringtree_append_printf(tree, "	if (value->$%.*s)", N);
							stringtree_append_printf(tree, "	{");
							stringtree_append_printf(tree, "		while (value->$%.*s->n + trie->$%.*s->n > value->$%.*s->cap)", N, N, N);
							stringtree_append_printf(tree, "		{");
							stringtree_append_printf(tree, "			value->$%.*s->cap = value->$%.*s->cap << 1 ?: 1;", N, N);
							stringtree_append_printf(tree, "			value->$%.*s->data = realloc(value->$%.*s->data, sizeof(*value->$%.*s->data) * value->$%.*s->cap);", N, N, N, N);
							stringtree_append_printf(tree, "		}");
							stringtree_append_printf(tree, "		memmove(value->$%.*s->data + trie->$%.*s->n, value->$%.*s->data, sizeof(*value->$%.*s->data) * value->$%.*s->n);", N, N, N, N, N);
							stringtree_append_printf(tree, "		for (unsigned i = 0, n = trie->$%.*s->n; i < n; i++)", N);
							stringtree_append_printf(tree, "		{");
							stringtree_append_printf(tree, "			value->$%.*s->data[i] = func_%u(trie->$%.*s->data[i]);", N, inc_id, N);
							stringtree_append_printf(tree, "		}");
							stringtree_append_printf(tree, "		value->$%.*s->n += trie->$%.*s->n;", N, N);
							stringtree_append_printf(tree, "	}");
							stringtree_append_printf(tree, "	else");
							stringtree_append_printf(tree, "	{");
							stringtree_append_printf(tree, "		value->$%.*s = func_%u(trie->$%.*s);", N, inc_array_id, N);
							stringtree_append_printf(tree, "	}");
							stringtree_append_printf(tree, "}");
							#undef N
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, type);
			
			stringtree_append_printf(tree, ""
					"func_%u(trie);"
				"}"
			"", free_id);
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


