
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "1.complement.h"
#include "2.range.h"

static unsigned char max(charset_t value)
{
	for (unsigned i = 255; 1 <= i + 1; i--)
		if (value[i >> 4] & (1 << (i & 0xF)))
			return i;
	return 0;
}

static unsigned char min(charset_t value)
{
	for (unsigned i = 0, n = 256; i < n; i++)
		if (value[i >> 4] & (1 << (i & 0xF)))
			return i;
	return 255;
}

charset_t read_charset_range_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	charset_t left = read_charset_complement_expression(tokenizer);
	
	if (tokenizer->token == t_dash)
	{
		read_token(tokenizer);
		
		charset_t right = read_charset_complement_expression(tokenizer);
		
		unsigned char l = min(left), r = max(right);
		
		dpv(l);
		dpv(r);
		
		charset_t range = {};
		
		for (unsigned i = l; i <= r; i++)
			range[i >> 4] |= (1 << (i & 0xF));
		
		left = range;
	}
	
	EXIT;
	return left;
}
