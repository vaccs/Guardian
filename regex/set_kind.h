
#include <enums/token_kind.h>

struct regex;

void regex_set_kind(
	struct regex* state,
	unsigned accepting,
	enum token_kind kind);
