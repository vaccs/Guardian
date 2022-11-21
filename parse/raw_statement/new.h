
#include <enums/assertion_kind.h>

struct zebu_expression;
struct gegex;
struct string;

struct raw_statement* new_raw_assertion(
	unsigned line,
	enum assertion_kind kind,
	struct zebu_expression* expression);

struct raw_statement* new_raw_declaration(
	struct string* name,
	struct zebu_expression* expression);

struct raw_statement* new_raw_print(
	struct zebu_expression* expression);

struct raw_statement* new_raw_parse(
	unsigned line,
	struct zebu_expression* expression,
	struct string* grammar_name,
	struct gegex* grammar);
	
