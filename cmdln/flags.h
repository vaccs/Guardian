
#include <stdbool.h>

struct cmdln
{
	const char* input_path;
	const char* output_path;
	
	bool minimize_lexer;
	
	bool verbose;
};

