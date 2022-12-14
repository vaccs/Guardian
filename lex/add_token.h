
#include <enums/token_kind.h>

struct regex;
struct lex;

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	enum token_kind kind);
