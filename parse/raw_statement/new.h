
#include <enums/assertion_kind.h>

struct zebu_expression;

struct raw_statement* new_raw_assertion(
	enum assertion_kind kind,
	struct zebu_expression* expression);

struct raw_statement* new_raw_declaration(
	struct string* name,
	struct zebu_expression* expression);

struct raw_statement* new_raw_print(
	struct zebu_expression* expression);
