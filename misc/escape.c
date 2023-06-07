
#include <assert.h>

#include <debug.h>

#include <memory/srealloc.h>

#include "escape.h"

char* escape(unsigned char* data)
{
	ENTER;
	
	dpvs(data);
	
	struct {
	  char* data;
	  unsigned n, cap;
	} buffer = {};
	
	void append(char c)
	{
    if (buffer.n == buffer.cap)
      buffer.data = srealloc(buffer.data, buffer.cap = buffer.cap << 1 ?: 1);
    buffer.data[buffer.n++] = c;
	}
	
	append('\"');
	
	for (unsigned char* m = data; *m; m++)
	  switch (*m)
	  {
	    case '+':
	    case '-':
	    case '/':
	    case '.':
	    case 'a' ... 'z':
	    case 'A' ... 'Z':
	    case '0' ... '9':
	      append((char) *m);
	      break;
	    
	    case '\n':
	      append('\\'), append('n');
	      break;
	    
	    default:
	      dpvc(*m);
	      TODO;
	      break;
	  }

	append('\"');
	
	append('\0');
	
	EXIT;
	return buffer.data;
}












