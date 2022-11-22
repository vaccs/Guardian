
struct regex;

struct expression* new_regex_match_expression(
	struct type* type,
	struct expression* base,
	struct regex* regex);
