
#include <debug.h>

#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_field.h>
#include <yacc/structinfo/free.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>

#include "../../tokenizer/struct.h"
#include "../../tokenizer/read_token.h"

#include "../../regex/4.root.h"

#include "regex.h"

#if 0
static struct format {
	struct {
		bool pound, zero, minus, space, plus, apostrophe;
	} flags;
	signed field_width, precision;
	char conversion_specifier;
} parse_format_string(
	const unsigned char* data,
	unsigned length)
{
	struct format format = {
		.field_width = -1,
		.precision = -1,
	};
	ENTER;
	
	if (!length)
	{
		TODO;
	}
	else if (*data == '%')
	{
		data++, length--;
	}
	else
	{
		TODO;
	}
	
	again: if (length) switch (*data)
	{
		case '#':  format.flags.pound = true; goto again;
		case '0':  format.flags.zero = true; goto again;
		case '-':  format.flags.minus = true; goto again;
		case ' ':  format.flags.space = true; goto again;
		case '+':  format.flags.plus = true; goto again;
		case '\'': format.flags.apostrophe = true; goto again;
	}
	
	if (length && memchr("0123456789", *data, 10))
	{
		format.field_width = 0;
		do format.field_width = format.field_width * 10 + *data++ - '0';
		while (length && memchr("0123456789", *data, 10));
	}
	
	if (length && *data == '.')
	{
		format.precision = 0, data++;
		
		while (length && memchr("0123456789", *data, 10))
			format.precision = format.precision * 10 + *data++ - '0';
	}
	
	if (!length)
	{
		TODO;
	}
	else switch (*data)
	{
		case 'd':
			TODO;
			break;
		case 'i':
			TODO;
			break;
		case 'o':
			TODO;
			break;
		case 'u':
			TODO;
			break;
		case 'x':
		case 'X':
			TODO;
			break;
		case 'e':
		case 'E':
			TODO;
			break;
		case 'f':
		case 'F':
			TODO;
			break;
		case 'g':
		case 'G':
			TODO;
			break;
		case 'a':
		case 'A':
			TODO;
			break;
		case 'c':
			TODO;
			break;
		case 's':
			TODO;
			break;
		case 'p':
			TODO;
			break;
		
		default:
			TODO;
			break;
	}
	
	TODO;
	
	EXIT;
	return format;
}
#endif

struct gbundle read_grammar_primary_regex_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_slash);
	
	read_token(tokenizer);
	
	struct rbundle nfa = read_regex_root_expression(tokenizer);
	
	if (tokenizer->token == t_colon)
	{
		read_token(tokenizer);
		
		if (tokenizer->token != t_string)
		{
			TODO;
			exit(1);
		}
		
		#if 0
		struct format format = parse_format_string(
			tokenizer->tokenchars.chars,
			tokenizer->tokenchars.n);
		#endif
		
		read_token(tokenizer);
	}
	
	if (tokenizer->token != t_slash)
	{
		TODO;
		exit(1);
	}
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_regex);
	
	dpv(token_id);
	
	struct structinfo* structinfo = new_structinfo();
	
	read_token(tokenizer);
	
	while (false
		|| tokenizer->token == t_scalar_hashtag
		|| tokenizer->token == t_array_hashtag)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_scalar_hashtag:
				structinfo_add_field(structinfo, tag, snt_token_string_scalar);
				break;
			
			case t_array_hashtag:
				TODO;
/*				structinfo_add_token_array_field(structinfo, tag);*/
				break;
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer);
		
		free_string(tag);
	}
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(start, token_id, whitespace, structinfo, end);
	
	free_structinfo(structinfo);
	free_unsignedset(whitespace);
	
	free_regex(nfa.start), free_regex(dfa);
	
	EXIT;
	return (struct gbundle) {start, end};
}





















