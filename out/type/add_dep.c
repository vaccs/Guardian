
#include <debug.h>

#include <set/ptr/add.h>

#include "struct.h"
#include "add_dep.h"

void out_type_add_dep(
	struct out_type* this,
	struct out_type* dep)
{
	ENTER;
	
	ptrset_add(this->dependent_on, dep);
	ptrset_add(dep->dependent_of, this);
	
	EXIT;
}

