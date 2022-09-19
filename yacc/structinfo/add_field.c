
#include <debug.h>

#include "struct.h"
#include "add_field.h"

#include "node/new.h"

void structinfo_add_field(
	struct structinfo* this,
	struct string* fieldname,
	struct string* grammar,
	enum structinfo_node_type fieldtype)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &fieldname);
	
	if (node)
	{
		TODO;
	}
	else
	{
		struct structinfo_node* node = new_structinfo_node(fieldname, grammar, fieldtype);
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}

