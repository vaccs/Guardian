
#include "kind.h"

struct zebu_expression;

struct assertion* new_assertion(
	enum assertion_kind kind,
	struct zebu_expression* expression);
