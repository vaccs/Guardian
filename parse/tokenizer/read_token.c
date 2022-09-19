
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
	s_comma,
	s_semicolon,
	s_osquare,
	s_csquare,
	s_oparen,
	s_cparen,
	s_qmark,
	s_asterisk,
	s_dash,
	s_emark,
	s_equals,
	
	s_directive,
	s_scalar_hashtag,
	s_array_hashtag,
	s_list_hashtag,
	s_identifier,
	s_character,
	s_string,
	
	s_start,
	
	s_read_slash,
	s_read_colon,
	s_read_dollar,
	s_read_vbar,
	s_read_comma,
	s_read_semicolon,
	s_read_osquare,
	s_read_csquare,
	s_read_oparen,
	s_read_cparen,
	s_read_qmark,
	s_read_asterisk,
	s_read_dash,
	s_read_emark,
	s_read_equals,
	
	s_reading_comment,
	
	s_reading_directive,
	
	s_reading_hashtag,
	s_reading_hashtag2,
	s_reading_hashtag3,
	
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
	
	[s_start][','] = s_read_comma,
		[s_read_comma][ANY] = s_comma,
	
	[s_start][';'] = s_read_semicolon,
		[s_read_semicolon][ANY] = s_semicolon,
	
	[s_start]['$'] = s_read_dollar,
		[s_read_dollar][ANY] = s_dollar,
	
	[s_start]['['] = s_read_osquare,
		[s_read_osquare][ANY] = s_osquare,
	
	[s_start][']'] = s_read_csquare,
		[s_read_csquare][ANY] = s_csquare,
	
	[s_start]['('] = s_read_oparen,
		[s_read_oparen][ANY] = s_oparen,
	
	[s_start][')'] = s_read_cparen,
		[s_read_cparen][ANY] = s_cparen,
	
	[s_start]['?'] = s_read_qmark,
		[s_read_qmark][ANY] = s_qmark,
	
	[s_start]['!'] = s_read_emark,
		[s_read_emark][ANY] = s_emark,
	
	[s_start]['*'] = s_read_asterisk,
		[s_read_asterisk][ANY] = s_asterisk,
	
	[s_start]['-'] = s_read_dash,
		[s_read_dash][ANY] = s_dash,
	
	[s_start]['='] = s_read_equals,
		[s_read_equals][ANY] = s_equals,
	
	// directives:
	[s_start]['%'] = s_reading_directive,
		[s_reading_directive][    ANY    ] = s_directive,
		[s_reading_directive]['a' ... 'z'] = s_reading_directive,
		[s_reading_directive]['A' ... 'Z'] = s_reading_directive,
	
	// hashtags:
	[s_start]['#'] = s_reading_hashtag,
		[s_reading_hashtag][    ANY    ] = s_scalar_hashtag,
		[s_reading_hashtag]['_'] = s_reading_hashtag,
		[s_reading_hashtag]['a' ... 'z'] = s_reading_hashtag,
		[s_reading_hashtag]['A' ... 'Z'] = s_reading_hashtag,
		[s_reading_hashtag]['['] = s_reading_hashtag2,
			[s_reading_hashtag2][']'] = s_reading_hashtag3,
				[s_reading_hashtag3][ANY] = s_array_hashtag,
	
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
		
		case s_slash:
			this->token = t_slash;
			break;
		
		case s_colon:
			this->token = t_colon;
			break;
		
		case s_vbar:
			this->token = t_vbar;
			break;
		
		case s_comma:
			this->token = t_comma;
			break;
		
		case s_dash:
			this->token = t_dash;
			break;
		
		case s_semicolon:
			this->token = t_semicolon;
			break;
		
		case s_osquare:
			this->token = t_osquare;
			break;
		
		case s_csquare:
			this->token = t_csquare;
			break;
		
		case s_oparen:
			this->token = t_oparen;
			break;
		
		case s_cparen:
			this->token = t_cparen;
			break;
		
		case s_qmark:
			this->token = t_qmark;
			break;
		
		case s_emark:
			this->token = t_emark;
			break;
		
		case s_asterisk:
			this->token = t_asterisk;
			break;
		
		case s_equals:
			this->token = t_equals;
			break;
		
		case s_directive:
			append(this, 0);
			this->token = t_directive;
			break;
		
		case s_scalar_hashtag:
		{
			// remove #:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 1;
			
			append(this, 0);
			this->token = t_scalar_hashtag;
			break;
		}
		
		case s_array_hashtag:
		{
			// remove # and []:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 3;
			
			append(this, 0);
			this->token = t_array_hashtag;
			break;
		}
		
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















