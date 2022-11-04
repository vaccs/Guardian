
#include <stdbool.h>

struct zpexpressionset;
struct zebu_primary_expression;

bool zpexpressionset_add(
	struct zpexpressionset* set,
	struct zebu_primary_expression* element);
