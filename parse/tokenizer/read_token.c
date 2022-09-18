
#include <debug.h>

#include "struct.h"
#include "read_char.h"
#include "read_token.h"

static void append(struct tokenizer* this, char c)
{
	ENTER;
	
	dpvc(c);
	
	if (this->tokenchars.n == this->tokenchars.cap)
	{
		this->tokenchars.cap = this->tokenchars.cap << 1 ?: 1;
		
		dpv(this->tokenchars.cap);
		
		this->tokenchars.chars = srealloc(this->tokenchars.chars, this->tokenchars.cap);
	}
	
	this->tokenchars.chars[this->tokenchars.n++] = c;
	
	EXIT;
}

static const enum state {
	s_error,
	
	// tokens:
	s_EOF,
	
	s_slash,
	s_dollar,
	s_colon,
	s_vbar,
	s_semicolon,
	
	s_directive,
	s_identifier,
	s_character,
	s_string,
	
	s_start,
	
	s_read_slash,
	s_read_colon,
	s_read_dollar,
	s_read_vbar,
	s_read_semicolon,
	
	s_reading_comment,
	s_reading_directive,
	
	s_reading_identifier,
	
	s_reading_character1, s_reading_character2, s_reading_character3, s_reading_character4,
	s_reading_string, s_read_string,
	
	number_of_states,
} machine[number_of_states][128] = {
	#define ANY 0 ... 127
	
	[s_start][' '] = s_start,
	[s_start]['\t'] = s_start,
	[s_start]['\n'] = s_start,
	
	// comments:
	[s_start]['/'] = s_read_slash,
		[s_read_slash][ANY] = s_slash,
		[s_read_slash]['/'] = s_reading_comment,
			[s_reading_comment][ANY] = s_reading_comment,
			[s_reading_comment]['\n'] = s_start,
	
	[s_start][':'] = s_read_colon,
		[s_read_colon][ANY] = s_colon,
	
	[s_start]['|'] = s_read_vbar,
		[s_read_vbar][ANY] = s_vbar,
	
	[s_start][';'] = s_read_semicolon,
		[s_read_semicolon][ANY] = s_semicolon,
	
	[s_start]['$'] = s_read_dollar,
		[s_read_dollar][ANY] = s_dollar,
	
	// directives:
	[s_start]['%'] = s_reading_directive,
		[s_reading_directive][    ANY    ] = s_directive,
		[s_reading_directive]['a' ... 'z'] = s_reading_directive,
		[s_reading_directive]['A' ... 'Z'] = s_reading_directive,
	
	// identifiers:
	[s_start]['a' ... 'z'] = s_reading_identifier,
	[s_start]['A' ... 'Z'] = s_reading_identifier,
		[s_reading_identifier][ANY] = s_identifier,
		[s_reading_identifier][    '_'    ] = s_reading_identifier,
		[s_reading_identifier]['a' ... 'z'] = s_reading_identifier,
		[s_reading_identifier]['A' ... 'Z'] = s_reading_identifier,
	
	// character literal:
	[s_start]['\''] = s_reading_character1,
		[s_reading_character1][ANY] = s_reading_character2,
			[s_reading_character2]['\''] = s_reading_character3,
				[s_reading_character3][ANY] = s_character,
		[s_reading_character1]['\\'] = s_reading_character4,
			[s_reading_character4][ANY] = s_reading_character2,
	
	// string literal:
	[s_start]['\"'] = s_reading_string,
		[s_reading_string][ANY] = s_reading_string,
		[s_reading_string]['\"'] = s_read_string,
			[s_read_string][ANY] = s_string,
};

void read_token(struct tokenizer* this)
{
	ENTER;
	
	dpvc(this->c);
	
	this->tokenchars.n = 0;
	
	enum state state = s_start;
	
	while (state >= s_start)
	{
		state = machine[state][(unsigned) this->c];
		
		if (state > s_start)
			append(this, this->c);
		else if (state == s_start)
			this->tokenchars.n = 0;
		
		if (state >= s_start)
			read_char(this);
	}
	
	dpvsn(this->tokenchars.chars, this->tokenchars.n);
	
	switch (state)
	{
		case s_error:
		{
			TODO;
			break;
		}
		
		case s_colon:
			this->token = t_colon;
			break;
		
		case s_vbar:
			this->token = t_vbar;
			break;
		
		case s_semicolon:
			this->token = t_semicolon;
			break;
		
		case s_directive:
			append(this, 0);
			this->token = t_directive;
			break;
		
		void escapes()
		{
			ENTER;
			
			unsigned char* s = this->tokenchars.chars;
			
			unsigned char* w = s, *r = w + 1, *n = w + this->tokenchars.n - 1;
			
			while (r < n)
			{
				dpvc(*r);
				
				if (*r != '\\')
					*w++ = *r++;
				else switch (*++r)
				{
					case 'n': *w++ = '\n', r++; break;
					
					case 't': *w++ = '\t', r++; break;
					
					case '\\': *w++ = '\\', r++; break;
					
					case '\'': *w++ = '\'', r++; break;
					
					case '\"': *w++ = '\"', r++; break;
					
					default:
					{
						dpvc(*r);
						TODO;
						break;
					}
				}
			}
			
			this->tokenchars.n = w - s;
			
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
			
			EXIT;
		}
		
		case s_character:
			escapes();
			this->token = t_character;
			break;
		
		case s_string:
			escapes();
			this->token = t_string;
			break;
		
		case s_identifier:
			append(this, 0);
			this->token = t_identifier;
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
}















