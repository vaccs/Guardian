
#include <stdbool.h>

#include <expression/variable/kind.h>

struct string;

void unresolved_foreach(
	const struct unresolved* this,
	void (*runme)(struct string* name));
	
void unresolved_foreach2(
	const struct unresolved* this,
	void (*runme)(
		struct string* name,
		enum variable_expression_kind kind,
		bool another));
	
void unresolved_foreach3(
	const struct unresolved* this,
	void (*runme)(
		struct string* name,
		struct type* type));
