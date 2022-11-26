
#include <assert.h>

#include <debug.h>

#include <memory/srealloc.h>

#include <parse/parse.h>

#include <type_cache/get_string_type.h>

#include <value/string/new.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include "string.h"

struct expression* specialize_primary_string_expression(
	struct type_cache* tcache,
	struct zebu_token* string_literal)
{
	ENTER;
	dpvs(string_literal->data);
	
	struct type* type = type_cache_get_string_type(tcache);
	
	struct {
		unsigned char* data;
		unsigned n, cap;
	} buffer = {};
	
	void append(unsigned char code)
	{
		if (buffer.n == buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, buffer.cap);
		}
		
		buffer.data[buffer.n++] = code;
	}
	
	for (unsigned i = 1, n = string_literal->len - 1; i < n; i++)
	{
		unsigned char code = string_literal->data[i];
		
		dpv(code);
		
		if (code != '\\')
		{
			append(code);
		}
		else switch ((code = string_literal->data[++i]))
		{
			case 't': append('\t'); break;
			
			case 'n': append('\n'); break;
			
			case '\\': append('\\'); break;
			
			case '\'':
				TODO;
				break;
			
			case '\"':
				TODO;
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	struct value* value = new_string_value(type, buffer.data, buffer.n);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}















