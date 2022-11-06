
#include <assert.h>

#include <debug.h>

#include "misc/escapes.h"

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
							
							escapes(token->data, token->len);
							
							unsigned char first = token->data[0];
							
							dpvc(first);
							
							retval[first >> 4] |= 1 << (first & 0xF);
						}
						else if (highest->integer)
						{
							TODO;
						}
						else if (highest->subcharset)
						{
							TODO;
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
			{
				TODO;
			}
			
			EXIT;
			return retval;
		}
		
		charset_t retval = intersect(symdiff->base);
		
		for (unsigned i = 0, n = symdiff->xors.n; i < n; i++)
		{
			TODO;
		}
		
		EXIT;
		return retval;
	}
	
	charset_t retval = symdiff(root->base);
	
	for (unsigned i = 0, n = root->ors.n; i < n; i++)
	{
		charset_t or = symdiff(root->ors.data[i]);
		
		retval |= or;
	}
	
	EXIT;
	return retval;
}


















