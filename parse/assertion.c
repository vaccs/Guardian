
#include <debug.h>

#include <set/ptr/add.h>

#include "assertion/new.h"

#include "assertion.h"

#include "parser.h"

void process_assertion(
	struct ptrset* assertions,
	struct zebu_assertion* assertion)
{
	ENTER;
	
	assert(assertion->expression);
	
	enum assertion_kind kind = ak_warning;
	
	if (assertion->debug)
		kind = ak_debug;
	else if (assertion->note)
		kind = ak_note;
	else if (assertion->warning)
		kind = ak_warning;
	else if (assertion->error)
		kind = ak_error;
	
	ptrset_add(assertions, new_assertion(kind, assertion->expression));
	
	EXIT;
}
