
#include <debug.h>

#include "escapes.h"

unsigned escapes(unsigned char* data, unsigned len)
{
	ENTER;
	
	dpvsn(data, len);
	
	unsigned char* s = data;
	
	unsigned char* w = s, *r = w + 1, *n = w + len - 1;
	
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
	
	len = w - s;
	
	dpvsn(data, len);
	
	EXIT;
	return len;
}












