

#include <enums/assertion_kind.h>

struct statement* new_assert_statement(
	unsigned line,
	enum assertion_kind kind,
	struct expression* expression);
