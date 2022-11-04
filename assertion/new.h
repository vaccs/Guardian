
#include <enums/assertion_kind.h>

struct expression;

struct assertion* new_assertion(
	enum assertion_kind kind,
	struct expression* expression);
