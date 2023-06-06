
#define _GNU_SOURCE

#include <string.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <quadmath.h>
#include <math.h>
#include <gmp.h>

#define N(array) (sizeof(array) / sizeof(*array))

struct token
{
	unsigned char* data;
	unsigned len;
};

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-function"
static void free_token(struct token* token)
{
	free(token->data);
	free(token);
}
#pragma GCC diagnostic pop

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

int main(int argc, char* const* argv)
{
	const char* const argv0 = argv[0];
	bool quiet = false;
	
	void usage(int code)
	{
		fprintf(stderr, "usage: %s: [-vh] <paths...>\n", argv0);
		exit(code);
	}
	
	int opt;
	while ((opt = getopt(argc, argv, "hq")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			case 'q':
				quiet = true;
				break;
			
			default:
				usage(1);
				break;
		}
	}
	
	if (quiet)
	{
		printf("print statements are suppressed.\n");
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
	
	#pragma GCC diagnostic push 
  #pragma GCC diagnostic ignored "-Wunused-function"
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
		
		#if 0
		void ddprintf(const char* fmt, ...)
		{
		    #ifdef PARSER_DEBUG
			for (unsigned i = 0, n = yacc.n; i < n; i++)
				printf("%u ", yacc.data[i]);
			
			printf("| ");
		    #endif
			
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
			
			#ifdef LEXER_DEBUG
			printf("lexer: \"%.*s\": l = %u\n", lexer.n, lexer.data, l);
			#endif
			
			while (1)
			{
				if (i < lexer.n)
				{
					c = lexer.data[i];
					
/*					#ifdef LEXER_DEBUG*/
/*					char escaped[10];*/
/*					*/
/*					escape(escaped, c);*/
/*					*/
/*					printf("lexer: c = '%s' (0x%X) (from cache)\n", escaped, c);*/
/*					#endif*/
					
					a = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;
				}
				else if ((c = getc(stream)) != EOF)
				{
					push_char(c);
					
/*					#ifdef LEXER_DEBUG*/
/*					char escaped[10];*/
/*					*/
/*					escape(escaped, c);*/
/*					*/
/*					printf("lexer: c = '%s' (0x%02hhX)\n", escaped, c);*/
/*					#endif*/
					
					a = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;
				}
				else
				{
					c = EOF;
					
/*					#ifdef LEXER_DEBUG*/
/*					printf("lexer: c = <EOF>\n");*/
/*					#endif*/
					
					a = l < N(lexer_EOFs) ? lexer_EOFs[l] : 0;
				}
				
				b = l < N(lexer_accepts) ? lexer_accepts[l] : 0;
				
				#ifdef LEXER_DEBUG
				printf("lexer: \"%.*s\" | \"%.*s\": a = %u, b = %u, t = %u, f = %u\n", i, lexer.data, lexer.n - i, lexer.data + i, a, b, t, f);
				#endif
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = i++;
						#ifdef LEXER_DEBUG
						printf("lexer: l = %u\n", l);
						#endif
					}
					else
					{
						l = a, i++;
						#ifdef LEXER_DEBUG
						printf("lexer: l = %u\n", l);
						#endif
					}
					
					if (c == '\n')
					{
						line++;
						#ifdef LEXER_DEBUG
						printf("lexer: line: %u\n", line);
						#endif
					}
				}
				else if (b)
				{
					#ifdef LEXER_DEBUG
					printf("lexer: token: \"%.*s\"\n", i, lexer.data);
					#endif
					
					if (!lexer.n)
					{
						#ifdef LEXER_DEBUG
						printf("lexer: EOF.\n");
						#endif
						t = b, td = NULL;
						break;
					}
					else if (b == 1)
					{
						#ifdef LEXER_DEBUG
						printf("lexer: whitespace\n");
						#endif
						
						l = original_l, t = 0, lexer.line = line;
						memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;
					}
					else
					{
						#ifdef LEXER_DEBUG
						printf("lexer: i = %u\n", i);
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
						#ifdef LEXER_DEBUG
						printf("lexer: falling back to whitespace: \"%.*s\"\n", f, lexer.data);
						#endif
						
						l = original_l, t = 0, line = lexer.line;
						memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;
					}
					else
					{
						#ifdef LEXER_DEBUG
						printf("lexer: falling back to token: \"%.*s\"\n", f, lexer.data);
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
    #pragma GCC diagnostic pop

		
		unsigned y = start_state_id, s, r;
		push_state(y), read_token(lexer_starts[y]);
		
		while (yacc.n)
		{
			if (y < N(shifts) && t < N(*shifts) && (s = shifts[y][t]))
			{
				#ifdef PARSER_DEBUG
				printf("s == %u\n", s);
				#endif
				
				y = s, push_state(y), push_data(td);
				
				read_token(lexer_starts[y]);
				
				#ifdef PARSER_DEBUG
				printf("t = %u\n", t);
				#endif
			}
			else if (y < N(reduces) && t < N(*reduces) && (r = reduces[y][t]))
			{
				#ifdef PARSER_DEBUG
				printf("r == %u\n", r);
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
					
					#ifdef PARSER_DEBUG
					printf("y = %u\n", y);
					#endif
					
					assert(y < N(gotos) && g < N(*gotos));
					
					s = gotos[y][g];
					
					#ifdef PARSER_DEBUG
					printf("s = %u\n", s);
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


























