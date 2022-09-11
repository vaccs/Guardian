
#include "token.h"

struct tokenizer
{
	int fd;
	
	struct {
		char data[4096];
		unsigned i, n;
	} buffer;
	
	char c;
	
	struct {
		char* chars;
		unsigned n, cap;
	} tokenchars;

	enum token token;
};

