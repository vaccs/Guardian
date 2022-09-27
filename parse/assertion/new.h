
#include <enums/assertion_kind.h>

struct zebu_expression;

struct raw_assertion* new_raw_assertion(
	enum assertion_kind kind,
	struct zebu_expression* expression);
