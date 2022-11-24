
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <math.h>
#include <gmp.h>

#define N(array) (sizeof(array) / sizeof(*array))

struct token
{
	unsigned char* data;
	unsigned len;
};

static void free_token(struct token* token)
{
	free(token->data);
	free(token);
}

// integers, booleans, lambdas, lists, tuples, ...
{{TYPES}}

// lambda captures:
{{SUBTYPES}}

// lexer tables:
{{LEXER_TRANSITION_TABLE}}

{{LEXER_ACCEPTS}}

{{LEXER_STARTS}}

{{LEXER_EOFS}}

// parser tables:
{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

#ifdef MAIA_DEBUG
static void escape(char *out, unsigned char in)
{
	switch (in)
	{
		case ' ':
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '=':
		case '|':
		case '/':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\'': *out++ = '\\', *out++ = '\'', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02hhX", in);
			break;
	}
}
#endif

int main(int argc, char* const* argv)
{
	const char* const argv0 = argv[0];
	bool verbose = false;
	
	void usage(int code)
	{
		fprintf(stderr, "usage: %s: [-vh] <paths...>\n", argv0);
		exit(code);
	}
	
	int opt;
	while ((opt = getopt(argc, argv, "hv")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			case 'v':
				verbose = true;
				break;
			
			default:
				usage(1);
				break;
		}
	}
	
	argv += optind;
	
	// declare root environment:
	{{DECLARE_ENVIRONMENT}}
	
	// new()s, inc()s, free()s, compare()s, index()s, ...
	{{FUNCTIONS}}
	
	// allocate root environment, init all fields to NULL:
	{{ASSIGN_ENVIRONMENT}}
	
	// assign sets:
	{{ASSIGN_SETS}}
	
	void* parse(
		FILE* stream,
		unsigned start_state_id,
		unsigned start_grammar_id)
	{
		void* start = NULL;
		
		struct { unsigned* data, n, cap; } yacc = {};
		struct { void** data; unsigned n, cap; } data = {};
		struct { unsigned char* data; unsigned n, cap; unsigned line; } lexer = {};
		
		lexer.line = 1;
		
		void push_state(unsigned y)
		{
			if (yacc.n + 1 >= yacc.cap)
			{
				yacc.cap = yacc.cap << 1 ?: 1;
				yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
			}
			yacc.data[yacc.n++] = y;
		}
		
		void push_data(void* d)
		{
			if (data.n + 1 >= data.cap)
			{
				data.cap = data.cap << 1 ?: 1;
				data.data = realloc(data.data, sizeof(*data.data) * data.cap);
			}
			data.data[data.n++] = d;
		}
		
		void push_char(unsigned char c)
		{
			while (lexer.n + 1 >= lexer.cap)
			{
				lexer.cap = lexer.cap << 1 ?: 1;
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		#ifdef MAIA_DEBUG
		void ddprintf(const char* fmt, ...)
		{
			for (unsigned i = 0, n = yacc.n; i < n; i++)
				printf("%u ", yacc.data[i]);
			
			printf("| ");
			
			va_list va;
			va_start(va, fmt);
			vprintf(fmt, va);
			va_end(va);
		}
		#endif
		
		unsigned t;
		void* td;
		
		void read_token(unsigned l)
		{
			unsigned original_l = l, i = 0, a, b, c, f = 0;
			
			unsigned line = lexer.line;
			
			t = 0, td = NULL;
			
			#ifdef MAIA_DEBUG
			ddprintf("lexer: \"%.*s\": l = %u\n", lexer.n, lexer.data, l);
			#endif
			
			while (1)
			{
				if (i < lexer.n)
				{
					c = lexer.data[i];
					
					#ifdef MAIA_DEBUG
					char escaped[10];
					
					escape(escaped, c);
					
					ddprintf("lexer: c = '%s' (0x%X) (from cache)\n", escaped, c);
					#endif
					
					a = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;
				}
				else if ((c = getc(stream)) != EOF)
				{
					push_char(c);
					
					#ifdef MAIA_DEBUG
					char escaped[10];
					
					escape(escaped, c);
					
					ddprintf("lexer: c = '%s' (0x%02hhX)\n", escaped, c);
					#endif
					
					a = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;
				}
				else
				{
					c = EOF;
					
					#ifdef MAIA_DEBUG
					ddprintf("lexer: c = <EOF>\n");
					#endif
					
					a = l < N(lexer_EOFs) ? lexer_EOFs[l] : 0;
				}
				
				b = l < N(lexer_accepts) ? lexer_accepts[l] : 0;
				
				#ifdef MAIA_DEBUG
				ddprintf("lexer: \"%.*s\" (%u): a = %u, b = %u\n", lexer.n, lexer.data, i, a, b);
				#endif
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, t = i++;
						#ifdef MAIA_DEBUG
						ddprintf("lexer: l = %u\n", l);
						#endif
					}
					else
					{
						l = a, i++;
						#ifdef MAIA_DEBUG
						ddprintf("lexer: l = %u\n", l);
						#endif
					}
					
					if (c == '\n')
					{
						line++;
						#ifdef MAIA_DEBUG
						ddprintf("lexer: line: %u\n", line);
						#endif
					}
				}
				else if (b)
				{
					#ifdef MAIA_DEBUG
					ddprintf("lexer: token: \"%.*s\"\n", i, lexer.data);
					#endif
					
					if (!lexer.n)
					{
						#ifdef MAIA_DEBUG
						ddprintf("lexer: EOF.\n");
						#endif
						t = b, td = NULL;
						break;
					}
					else if (b == 1)
					{
						#ifdef MAIA_DEBUG
						ddprintf("lexer: whitespace\n");
						#endif
						
						l = original_l, t = 0, lexer.line = line;
						memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;
					}
					else
					{
						#ifdef MAIA_DEBUG
						ddprintf("lexer: i = %u\n", i);
						#endif
						
						struct token* token = malloc(sizeof(*token));
						token->data = memcpy(malloc(i + 1), lexer.data, i);
						token->data[i] = 0;
						token->len = i;
						t = b, td = token;
						
						lexer.line = line;
						memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;
						break;
					}
				}
				else if (t)
				{
					if (t == 1)
					{
						#ifdef MAIA_DEBUG
						ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", f, lexer.data);
						#endif
						
						l = original_l, t = 0, line = lexer.line;
						memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;
					}
					else
					{
						#ifdef MAIA_DEBUG
						ddprintf("lexer: falling back to token: \"%.*s\"\n", f, lexer.data);
						#endif
						
						struct token* token = malloc(sizeof(*token));
						token->data = memcpy(malloc(f + 1), lexer.data, f);
						token->data[f] = 0;
						token->len = f;
						td = token;
						
						memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;
						break;
					}
				}
				else
				{
					if (c == (unsigned) EOF)
						fprintf(stderr, "%s: unexpected '<EOF>' when reading '%.*s' on line %u!\n", argv0, i, lexer.data, line);
					else
						fprintf(stderr, "%s: unexpected '%c' when reading '%.*s' on line %u!\n", argv0, c, i, lexer.data, line);
					
					exit(1);
				}
			}
		}
		
		unsigned y = start_state_id, s, r;
		push_state(y), read_token(lexer_starts[y]);
		
		while (yacc.n)
		{
			if (y < N(shifts) && t < N(*shifts) && (s = shifts[y][t]))
			{
				#ifdef MAIA_DEBUG
				ddprintf("s == %u\n", s);
				#endif
				
				y = s, push_state(y), push_data(td);
				
				read_token(lexer_starts[y]);
				
				#ifdef MAIA_DEBUG
				ddprintf("t = %u\n", t);
				#endif
			}
			else if (y < N(reduces) && t < N(*reduces) && (r = reduces[y][t]))
			{
				#ifdef MAIA_DEBUG
				ddprintf("r == %u\n", r);
				#endif
				
				unsigned g;
				void* d;
				
				{{REDUCTION_RULE_SWITCH}}
				
				if (g == start_grammar_id)
				{
					yacc.n = 0, start = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					#ifdef MAIA_DEBUG
					ddprintf("y = %u\n", y);
					#endif
					
					assert(y < N(gotos) && g < N(*gotos));
					
					s = gotos[y][g];
					
					#ifdef MAIA_DEBUG
					ddprintf("s = %u\n", s);
					#endif
					
					y = s, push_state(y), push_data(d);
				}
			}
			else
			{
				assert(!"266");
			}
		}
		
		free(yacc.data);
		free(data.data);
		free(lexer.data);
		
		return start;
	}
	
	// statements:
	{{STATEMENTS}}
	
	// clean up declarations:
	{{FREE_ENVIRONMENT}}
	
	return 0;
}


























