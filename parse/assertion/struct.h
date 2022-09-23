
#include "kind.h"

struct assertion
{
	enum assertion_kind kind;
	
	struct zebu_expression* expression; // owned. free when done.
};

