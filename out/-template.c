
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include <gmp.h>

#define N(array) (sizeof(array) / sizeof(*array))

// integers, booleans, lambdas, lists, tuples, ...
{{STRUCTS}}

// any '%forward' value-declares:
{{FORWARD_DECLARES}}

// new()s, inc()s, free()s, compare()s, index()s, ...
{{FUNCTIONS}}

// lexer tables:
{{LEXER_TRANSITION_TABLE}}

// parser tables:

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

int main(int argc, char* const* argv)
{
	const char* const argv0 = argv[0];
	
	void usage(int code)
	{
		fprintf(stderr, "usage: %s: [-vh] <input-file>\n", argv0);
		exit(code);
	}
	
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			default:
				usage(1);
				break;
		}
	}
	
	const char* const input_path = argv[optind++];
	
	if (!input_path)
		usage(1);
	
	FILE* stream = fopen(input_path, "r");
	
	if (!stream)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, input_path);
		exit(1);
	}
	
	// create sets:
	{{INIT_SETS}}
	
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data; unsigned n, cap; } data = {};
	struct { unsigned char* data; unsigned n, cap; } lexer = {};
	
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
	
	unsigned t;
	void* td;
	
	void read_token(unsigned l)
	{
		unsigned original_l = l, i = 0, a, b, c, f = 0;
		
		t = 0, td = NULL;
		
		ddprintf("lexer: \"%.*s\": l = %u\n", lexer.n, lexer.data, l);
		
		while (1)
		{
			if (i < lexer.n)
			{
				assert(!"TODO");
				#if 0
				c = lexer.data[i];
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%X) (from cache)\n", escaped, c);
				
				a = l < N(lexer) && c < N(*lexer) ? lexer[l][c] : 0;
				#endif
			}
			else if ((c = getc(stream)) != EOF)
			{
				push_char(c);
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%02hhX)\n", escaped, c);
				
				a = l < N(lexer_transitions) && c < N(*lexer_transitions) ? lexer_transitions[l][c] : 0;
			}
			else
			{
				assert(!"TODO");
				#if 0
				c = EOF;
				
				ddprintf("lexer: c = <EOF>\n");
				
				a = l < N(lexer_EOFs) ? lexer_EOFs[l] : 0;
				#endif
			}
			
			assert(!"TODO");
			#if 0
			b = l < N(lexer_accepts) ? lexer_accepts[l] : 0;
			
			ddprintf("lexer: \"%.*s\" (%u): a = %u, b = %u\n", lexer.n, lexer.data, i, a, b);
			#endif
			
			if (a)
			{
				if (b)
				{
					assert(!"TODO");
					#if 0
					l = a, t = b, f = i++;
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
				else
				{
					assert(!"TODO");
					#if 0
					l = a, i++;
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
			}
			else if (b)
			{
				ddprintf("lexer: token: \"%.*s\"\n", i, lexer.data);
				
				if (!lexer.n)
				{
					assert(!"TODO");
					#if 0
					ddprintf("lexer: EOF.\n");
					t = b, td = NULL;
					break;
					#endif
				}
				else if (b == 1)
				{
					assert(!"TODO");
					#if 0
					ddprintf("lexer: whitespace: \"%.*s\"\n", i, lexer.data);
					
					l = original_l, t = 0;
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;
					#endif
				}
				else
				{
					assert(!"TODO");
					#if 0
					ddprintf("lexer: i = %u\n", i);
					
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(i + 1), lexer.data, i);
					token->data[i] = 0;
					token->len = i;
					t = b, td = token;
					
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;
					break;
					#endif
				}
			}
			else if (f)
			{
				if (t == 1)
				{
					assert(!"TODO");
					#if 0
					ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", f, lexer.data);
					
					l = original_l, t = 0;
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;
					#endif
				}
				else
				{
					assert(!"TODO");
					#if 0
					ddprintf("lexer: falling back to token: \"%.*s\"\n", f, lexer.data);
					
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(f + 1), lexer.data, f);
					token->data[f] = 0;
					token->len = f;
					td = token;
					
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;
					break;
					#endif
				}
			}
			else
			{
				fprintf(stderr, "%s: unexpected '%c' when reading ...'%.*s'!\n", argv0, c, i, lexer.data);
				abort();
			}
		}
	}
	
	unsigned y = 1;
	push_state(y), read_token(1);
	
	assert(!"TODO");
	
	// variable declarations:
	{{INIT_DECLARES}}
	
	// assertions:
	{{ASSERTIONS}}
	
	// clean up declarations:
	{{UNINIT_DECLARES}}
	
	// clean up sets:
	{{UNINIT_SETS}}
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return 0;
}


















