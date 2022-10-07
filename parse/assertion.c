
#include <debug.h>

#include <quack/append.h>

#include "assertion/new.h"

#include "assertion.h"

#include "parse.h"

void process_assertion(
	struct quack* assertions,
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
	
	quack_append(assertions, new_raw_assertion(kind, assertion->expression));
	
	EXIT;
}
