
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <misc/unescape.h>

#include "parse.h"
#include "charset.h"

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

charset_t process_charset(
	struct zebu_charset* root)
{
	ENTER;
		
	charset_t symdiff(struct zebu_charset_symdiff* symdiff)
	{
		ENTER;
		
		charset_t intersect(struct zebu_charset_intersect* intersect)
		{
			ENTER;
			
			charset_t range(struct zebu_charset_range* range)
			{
				ENTER;
				
				charset_t prefix(struct zebu_charset_prefix* prefix)
				{
					ENTER;
					
					charset_t highest(struct zebu_charset_highest* highest)
					{
						charset_t retval = {};
						ENTER;
						
						if (highest->character)
						{
							struct zebu_token* token = highest->character;
							
							unescape(token->data, token->len);
							
							unsigned char first = token->data[0];
							
							dpvc(first);
							
							retval[first >> 4] |= 1 << (first & 0xF);
						}
						else if (highest->integer)
						{
							errno = 0;
							
							const char* token = (void*) highest->integer->data;
							char* m;
							unsigned long int value = strtoul(token, &m, 0);
							
							if (errno || *m || value > 255)
							{
								fprintf(stderr, "%s: invalid integer value '%s' for character in charset!\n", argv0, token);
								exit(1);
							}
							
							retval[value >> 4] = 1 << (value & 0xF);
						}
						else if (highest->subcharset)
						{
							retval = process_charset(highest->subcharset);
						}
						else
						{
							TODO;
						}
						
						EXIT;
						return retval;
					}
					
					charset_t retval = highest(prefix->base);
					
					if (prefix->emark)
						retval = ~retval;
					
					EXIT;
					return retval;
				}
				
				charset_t left = prefix(range->left);
				
				if (range->right)
				{
					charset_t right = prefix(range->right);
					
					unsigned char l = min(left), r = max(right);
					
					dpv(l);
					dpv(r);
					
					for (unsigned i = l; i <= r; i++)
						left[i >> 4] |= (1 << (i & 0xF));
				}
				
				EXIT;
				return left;
			}
			
			charset_t retval = range(intersect->base);
			
			for (unsigned i = 0, n = intersect->intersects.n; i < n; i++)
				retval &= range(intersect->intersects.data[i]);
			
			EXIT;
			return retval;
		}
		
		charset_t retval = intersect(symdiff->base);
		
		for (unsigned i = 0, n = symdiff->xors.n; i < n; i++)
			retval ^= intersect(symdiff->xors.data[i]);
		
		EXIT;
		return retval;
	}
	
	charset_t retval = symdiff(root->base);
	
	for (unsigned i = 0, n = root->ors.n; i < n; i++)
		retval |= symdiff(root->ors.data[i]);
	
	EXIT;
	return retval;
}


















