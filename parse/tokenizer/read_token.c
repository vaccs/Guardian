
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
	
	// identifer:
	s_identifier,
	
	// keywords:
	s_using_,
	
	// literals:
	s_string,
	
	// start state:
	s_start,
	
	// reading keywords:
	s_u, s_us, s_usi, s_usin, s_using,
	
	// reading identifer:
	s_reading_identifier,
	
	// reading string literal:
	s_reading_string, s_read_string,
	
	number_of_states,
} machine[number_of_states][128] = {
	#define ANY 0 ... 127
	
	[s_start][' '] = s_start,
	[s_start]['\t'] = s_start,
	[s_start]['\n'] = s_start,
	
	// identifiers:
	[s_start]['a' ... 'z'] = s_reading_identifier,
	[s_start]['A' ... 'Z'] = s_reading_identifier,
		[s_reading_identifier][ANY] = s_identifier,
		[s_reading_identifier]['a' ... 'z'] = s_reading_identifier,
		[s_reading_identifier]['A' ... 'Z'] = s_reading_identifier,
	
	// reading keywords:
	[s_start]['u'] = s_u,
		[s_u]['a' ... 'z'] = s_reading_identifier,
		[s_u]['s'] = s_us,
			[s_us]['a' ... 'z'] = s_reading_identifier,
			[s_us]['i'] = s_usi,
				[s_usi]['a' ... 'z'] = s_reading_identifier,
				[s_usi]['n'] = s_usin,
					[s_usin]['a' ... 'z'] = s_reading_identifier,
					[s_usin]['g'] = s_using,
						[s_using][ANY] = s_using_,
						[s_using]['a' ... 'z'] = s_reading_identifier,
	
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
	
	switch (state)
	{
		case s_error:
			TODO;
			break;
		
		case s_using_:
			this->token = t_using;
			break;
		
		void escapes()
		{
			ENTER;
			
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
			
			char* s = this->tokenchars.chars;
			
			char* w = s, *r = w + 1, *n = w + this->tokenchars.n - 1;
			
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















