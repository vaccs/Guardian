
#include "type.h"

struct structinfo_node* new_structinfo_node(
	enum structinfo_node_type type,
	struct string* name,
	struct string* grammar,
	char conversion_char);
