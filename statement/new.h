
#include "kind.h"

struct statement_inheritance;

struct statement* new_statement(
	unsigned line,
	enum statement_kind kind,
	struct statement_inheritance* inheritance,
	unsigned alloc_size);

#if 0
#include <enums/assertion_kind.h>

struct string;
struct expression;

struct statement* new_assert_statement(
	unsigned line,
	enum assertion_kind assertion_kind,
	struct expression* expression);
	
struct statement* new_declare_statement(
	struct string* name,
	struct expression* expression);
	
#endif
