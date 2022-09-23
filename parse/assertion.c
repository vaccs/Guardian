
#include <debug.h>

#include <set/ptr/add.h>

#include "assertion/new.h"

#include "assertion.h"

#include "parser.h"

void process_assertion(
	struct ptrset* assertions,
	struct zebu_entry* entry)
{
	ENTER;
	
	assert(entry->assertion);
	
	enum assertion_kind kind = ak_warning;
	
	if (entry->debug)
		kind = ak_debug;
	else if (entry->note)
		kind = ak_note;
	else if (entry->warning)
		kind = ak_warning;
	else if (entry->error)
		kind = ak_error;
	
	ptrset_add(assertions, new_assertion(kind, entry->assertion));
	
	EXIT;
}
