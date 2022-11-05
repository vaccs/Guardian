
#include <enums/token_kind.h>

struct regex
{
	struct regex* transitions[256], *EOF_transition_to;
	
	struct {
		struct regex** data;
		unsigned n, cap;
	} lambdas;
	
	enum token_kind kind;
	
	unsigned accepts;
};

