
struct type;
struct string_value;
struct regex;

struct value* regex_match_run(
	struct type* type,
	struct string_value* string,
	struct regex* regex);
