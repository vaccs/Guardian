
#include <debug.h>

#include "struct.h"
#include "add_field.h"

#include "node/new.h"

void structinfo_add_field(
	struct structinfo* this,
	enum structinfo_node_type fieldtype,
	struct string* fieldname,
	struct string* grammar)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &fieldname);
	
	if (node)
	{
		TODO;
	}
	else
	{
		struct structinfo_node* node = new_structinfo_node(fieldtype, fieldname, grammar, 0);
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}

