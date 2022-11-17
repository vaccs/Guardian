
#include <enums/assertion_kind.h>

struct string;
struct expression;

struct statement* new_assert_statement(
	enum assertion_kind assertion_kind,
	struct expression* expression);
	
struct statement* new_declare_statement(
	struct string* name,
	struct expression* expression);
	
struct statement* new_print_statement(
	struct expression* expression);
