
#include <debug.h>

#include <type/struct.h>
#include <type/environment/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* lambda_value_generate_generate_typedef(
	struct lambda_value* this,
	struct subtype_queue* squeue,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned type_id = this->super.type->id;
	
	dpv(this->id);
	
	stringtree_append_printf(tree, "struct subtype_%u", this->id);
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree, "struct type_%u super;", type_id);
	
	if (this->captured)
	{
		stringtree_append_printf(tree, "struct type_%u* captured;", this->captured->type->id);
	}
	
	stringtree_append_printf(tree, "};");
	
	EXIT;
	return tree;
}

