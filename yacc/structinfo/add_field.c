
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "add_field.h"

#include "node/new.h"

void structinfo_add_field(
	struct structinfo* this,
	enum structinfo_node_type fieldtype,
	struct string* fieldname,
	struct string* grammar,
	struct zebu_tokentype* tokentype)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &fieldname);
	
	if (node)
	{
		TODO;
	}
	else
	{
		struct structinfo_node* node = new_structinfo_node(fieldtype, fieldname, grammar, tokentype);
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}

