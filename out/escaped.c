const char* template = ""
	"" "\n"
	"#include <errno.h>" "\n"
	"#include <string.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <unistd.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <stdbool.h>" "\n"
	"#include <stdarg.h>" "\n"
	"" "\n"
	"#include <math.h>" "\n"
	"#include <gmp.h>" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"struct token" "\n"
	"{" "\n"
	"\tunsigned char* data;" "\n"
	"\tunsigned len;" "\n"
	"};" "\n"
	"" "\n"
	"static void free_token(struct token* token)" "\n"
	"{" "\n"
	"\tfree(token->data);" "\n"
	"\tfree(token);" "\n"
	"}" "\n"
	"" "\n"
	"// integers, booleans, lambdas, lists, tuples, ..." "\n"
	"{{TYPES}}" "\n"
	"" "\n"
	"// lambda captures:" "\n"
	"{{SUBTYPES}}" "\n"
	"" "\n"
	"// lexer tables:" "\n"
	"{{LEXER_TRANSITION_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_ACCEPTS}}" "\n"
	"" "\n"
	"{{LEXER_STARTS}}" "\n"
	"" "\n"
	"{{LEXER_EOFS}}" "\n"
	"" "\n"
	"// parser tables:" "\n"
	"{{SHIFT_TABLE}}" "\n"
	"" "\n"
	"{{REDUCE_TABLE}}" "\n"
	"" "\n"
	"{{GOTO_TABLE}}" "\n"
	"" "\n"
	"#ifdef MAIA_DEBUG" "\n"
	"static void escape(char *out, unsigned char in)" "\n"
	"{" "\n"
	"\tswitch (in)" "\n"
	"\t{" "\n"
	"\t\tcase \' \':" "\n"
	"\t\tcase \'~\':" "\n"
	"\t\tcase \'!\':" "\n"
	"\t\tcase \'@\':" "\n"
	"\t\tcase \'#\':" "\n"
	"\t\tcase \'$\':" "\n"
	"\t\tcase \'%\':" "\n"
	"\t\tcase \'^\':" "\n"
	"\t\tcase \'&\':" "\n"
	"\t\tcase \'*\':" "\n"
	"\t\tcase \'-\':" "\n"
	"\t\tcase \'+\':" "\n"
	"\t\tcase \'=\':" "\n"
	"\t\tcase \'|\':" "\n"
	"\t\tcase \'/\':" "\n"
	"\t\tcase \'<\': case \'>\':" "\n"
	"\t\tcase \'(\': case \')\':" "\n"
	"\t\tcase \'{\': case \'}\':" "\n"
	"\t\tcase \'[\': case \']\':" "\n"
	"\t\tcase \':\': case \';\':" "\n"
	"\t\tcase \',\': case \'.\':" "\n"
	"\t\tcase \'_\':" "\n"
	"\t\tcase \'0\' ... \'9\':" "\n"
	"\t\tcase \'a\' ... \'z\':" "\n"
	"\t\tcase \'A\' ... \'Z\':" "\n"
	"\t\t\t*out++ = in;" "\n"
	"\t\t\t*out = 0;" "\n"
	"\t\t\tbreak;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\\\\': *out++ = \'\\\\\', *out++ = \'\\\\\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\\'\': *out++ = \'\\\\\', *out++ = \'\\\'\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\\"\': *out++ = \'\\\\\', *out++ = \'\\\"\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\t\': *out++ = \'\\\\\', *out++ = \'t\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\n\': *out++ = \'\\\\\', *out++ = \'n\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tdefault:" "\n"
	"\t\t\tsprintf(out, \"\\\\x%02hhX\", in);" "\n"
	"\t\t\tbreak;" "\n"
	"\t}" "\n"
	"}" "\n"
	"#endif" "\n"
	"" "\n"
	"int main(int argc, char* const* argv)" "\n"
	"{" "\n"
	"\tconst char* const argv0 = argv[0];" "\n"
	"\tbool verbose = false;" "\n"
	"\t" "\n"
	"\tvoid usage(int code)" "\n"
	"\t{" "\n"
	"\t\tfprintf(stderr, \"usage: %s: [-vh] <paths...>\\n\", argv0);" "\n"
	"\t\texit(code);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tint opt;" "\n"
	"\twhile ((opt = getopt(argc, argv, \"hv\")) != -1)" "\n"
	"\t{" "\n"
	"\t\tswitch (opt)" "\n"
	"\t\t{" "\n"
	"\t\t\tcase \'h\':" "\n"
	"\t\t\t\tusage(0);" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t" "\n"
	"\t\t\tcase \'v\':" "\n"
	"\t\t\t\tverbose = true;" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t" "\n"
	"\t\t\tdefault:" "\n"
	"\t\t\t\tusage(1);" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\targv += optind;" "\n"
	"\t" "\n"
	"\t// declare root environment:" "\n"
	"\t{{DECLARE_ENVIRONMENT}}" "\n"
	"\t" "\n"
	"\t// new()s, inc()s, free()s, compare()s, index()s, ..." "\n"
	"\t{{FUNCTIONS}}" "\n"
	"\t" "\n"
	"\t// allocate root environment, init all fields to NULL:" "\n"
	"\t{{ASSIGN_ENVIRONMENT}}" "\n"
	"\t" "\n"
	"\t// assign sets:" "\n"
	"\t{{ASSIGN_SETS}}" "\n"
	"\t" "\n"
	"\tvoid* parse(" "\n"
	"\t\tFILE* stream," "\n"
	"\t\tunsigned start_state_id," "\n"
	"\t\tunsigned start_grammar_id)" "\n"
	"\t{" "\n"
	"\t\tvoid* start = NULL;" "\n"
	"\t\t" "\n"
	"\t\tstruct { unsigned* data, n, cap; } yacc = {};" "\n"
	"\t\tstruct { void** data; unsigned n, cap; } data = {};" "\n"
	"\t\tstruct { unsigned char* data; unsigned n, cap; unsigned line; } lexer = {};" "\n"
	"\t\t" "\n"
	"\t\tvoid push_state(unsigned y)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (yacc.n + 1 >= yacc.cap)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tyacc.cap = yacc.cap << 1 ?: 1;" "\n"
	"\t\t\t\tyacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);" "\n"
	"\t\t\t}" "\n"
	"\t\t\tyacc.data[yacc.n++] = y;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tvoid push_data(void* d)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (data.n + 1 >= data.cap)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tdata.cap = data.cap << 1 ?: 1;" "\n"
	"\t\t\t\tdata.data = realloc(data.data, sizeof(*data.data) * data.cap);" "\n"
	"\t\t\t}" "\n"
	"\t\t\tdata.data[data.n++] = d;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tvoid push_char(unsigned char c)" "\n"
	"\t\t{" "\n"
	"\t\t\twhile (lexer.n + 1 >= lexer.cap)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tlexer.cap = lexer.cap << 1 ?: 1;" "\n"
	"\t\t\t\tlexer.data = realloc(lexer.data, lexer.cap);" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tlexer.data[lexer.n++] = c;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\tvoid ddprintf(const char* fmt, ...)" "\n"
	"\t\t{" "\n"
	"\t\t\tfor (unsigned i = 0, n = yacc.n; i < n; i++)" "\n"
	"\t\t\t\tprintf(\"%u \", yacc.data[i]);" "\n"
	"\t\t\t" "\n"
	"\t\t\tprintf(\"| \");" "\n"
	"\t\t\t" "\n"
	"\t\t\tva_list va;" "\n"
	"\t\t\tva_start(va, fmt);" "\n"
	"\t\t\tvprintf(fmt, va);" "\n"
	"\t\t\tva_end(va);" "\n"
	"\t\t}" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\tunsigned t;" "\n"
	"\t\tvoid* td;" "\n"
	"\t\t" "\n"
	"\t\tvoid read_token(unsigned l)" "\n"
	"\t\t{" "\n"
	"\t\t\tunsigned original_l = l, i = 0, a, b, c, f = 0;" "\n"
	"\t\t\t" "\n"
	"\t\t\tunsigned line = lexer.line;" "\n"
	"\t\t\t" "\n"
	"\t\t\tt = 0, td = NULL;" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\tddprintf(\"lexer: \\\"%.*s\\\": l = %u\\n\", lexer.n, lexer.data, l);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\twhile (1)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (i < lexer.n)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tc = lexer.data[i];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tddprintf(\"lexer: c = \'%s\' (0x%X) (from cache)\\n\", escaped, c);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ta = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if ((c = getc(stream)) != EOF)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tpush_char(c);" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tddprintf(\"lexer: c = \'%s\' (0x%02hhX)\\n\", escaped, c);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ta = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tc = EOF;" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: c = <EOF>\\n\");" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ta = l < N(lexer_EOFs) ? lexer_EOFs[l] : 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tb = l < N(lexer_accepts) ? lexer_accepts[l] : 0;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\tddprintf(\"lexer: \\\"%.*s\\\" (%u): a = %u, b = %u\\n\", lexer.n, lexer.data, i, a, b);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (a)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (b)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tl = a, t = b, t = i++;" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: l = %u\\n\", l);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tl = a, i++;" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: l = %u\\n\", l);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tif (c == \'\\n\')" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tline++;" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: line: %u\\n\", line);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if (b)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: token: \\\"%.*s\\\"\\n\", i, lexer.data);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tif (!lexer.n)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: EOF.\\n\");" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\tt = b, td = NULL;" "\n"
	"\t\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse if (b == 1)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: whitespace\\n\");" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tl = original_l, t = 0, lexer.line = line;" "\n"
	"\t\t\t\t\t\tmemmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: i = %u\\n\", i);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tstruct token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\t\ttoken->data = memcpy(malloc(i + 1), lexer.data, i);" "\n"
	"\t\t\t\t\t\ttoken->data[i] = 0;" "\n"
	"\t\t\t\t\t\ttoken->len = i;" "\n"
	"\t\t\t\t\t\tt = b, td = token;" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tlexer.line = line;" "\n"
	"\t\t\t\t\t\tmemmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;" "\n"
	"\t\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if (t)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (t == 1)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: falling back to whitespace: \\\"%.*s\\\"\\n\", f, lexer.data);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tl = original_l, t = 0, line = lexer.line;" "\n"
	"\t\t\t\t\t\tmemmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: falling back to token: \\\"%.*s\\\"\\n\", f, lexer.data);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tstruct token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\t\ttoken->data = memcpy(malloc(f + 1), lexer.data, f);" "\n"
	"\t\t\t\t\t\ttoken->data[f] = 0;" "\n"
	"\t\t\t\t\t\ttoken->len = f;" "\n"
	"\t\t\t\t\t\ttd = token;" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tmemmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;" "\n"
	"\t\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (c == (unsigned) EOF)" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'<EOF>\' when reading \'%.*s\' on line %u!\\n\", argv0, i, lexer.data, line);" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'%c\' when reading \'%.*s\' on line %u!\\n\", argv0, c, i, lexer.data, line);" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\texit(1);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tunsigned y = start_state_id, s, r;" "\n"
	"\t\tpush_state(y), read_token(lexer_starts[y]);" "\n"
	"\t\t" "\n"
	"\t\twhile (yacc.n)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (y < N(shifts) && t < N(*shifts) && (s = shifts[y][t]))" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\tddprintf(\"s == %u\\n\", s);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ty = s, push_state(y), push_data(td);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tread_token(lexer_starts[y]);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\tddprintf(\"t = %u\\n\", t);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (y < N(reduces) && t < N(*reduces) && (r = reduces[y][t]))" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\tddprintf(\"r == %u\\n\", r);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tunsigned g;" "\n"
	"\t\t\t\tvoid* d;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t{{REDUCTION_RULE_SWITCH}}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (g == start_grammar_id)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tyacc.n = 0, start = d;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\ty = yacc.data[yacc.n - 1];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"y = %u\\n\", y);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tassert(y < N(gotos) && g < N(*gotos));" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ts = gotos[y][g];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef MAIA_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"s = %u\\n\", s);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ty = s, push_state(y), push_data(d);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"266\");" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tfree(yacc.data);" "\n"
	"\t\tfree(data.data);" "\n"
	"\t\tfree(lexer.data);" "\n"
	"\t\t" "\n"
	"\t\treturn start;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\t// statements:" "\n"
	"\t{{STATEMENTS}}" "\n"
	"\t" "\n"
	"\t// clean up declarations:" "\n"
	"\t{{FREE_ENVIRONMENT}}" "\n"
	"\t" "\n"
	"\treturn 0;" "\n"
	"}" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"";
