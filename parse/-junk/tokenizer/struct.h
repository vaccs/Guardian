
#include "token.h"

struct tokenizer
{
	int fd;
	
	struct {
		unsigned char data[4096];
		unsigned i, n;
	} buffer;
	
	char c;
	
	struct {
		unsigned char* chars;
		unsigned n, cap;
	} tokenchars;

	enum token token;
};

