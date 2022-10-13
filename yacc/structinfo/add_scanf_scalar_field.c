
#include <assert.h>
#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/insert.h>*/

/*#include <memory/smalloc.h>*/

/*#include <string/inc.h>*/

/*#include <misc/format_flags/inc.h>*/

#include "struct.h"
#include "node/new.h"
#include "add_scanf_scalar_field.h"

void structinfo_add_scanf_scalar_field(
	struct structinfo* this,
	struct string* fieldname,
	char conversion_char)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &fieldname);
	
	if (node)
	{
		// check that it's not already in there, or that it's not the wrong type
		TODO;
	}
	else
	{
		struct structinfo_node* node = new_structinfo_node(snt_scanf_scalar, fieldname, NULL, conversion_char);
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}


















