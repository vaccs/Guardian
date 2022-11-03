
#include "node/type.h"

void structinfo_add_field(
	struct structinfo* this,
	enum structinfo_node_type fieldtype,
	struct string* fieldname,
	struct string* grammar,
	struct zebu_tokentype* tokentype);
