
#include <assert.h>

#include <debug.h>

#include <quack/append.h>

#include <list/raw_assertion/append.h>

#include "assertion/new.h"
#include "assertion/free.h"

#include "assertion.h"

#include "parse.h"

void process_assertion(
	struct raw_assertion_list* assertions,
	struct zebu_assertion* assertion)
{
	ENTER;
	
	assert(assertion->expression);
	
	enum assertion_kind kind;
	
	if (assertion->debug)
		kind = ak_debug;
	else if (assertion->note)
		kind = ak_note;
	else if (assertion->warning)
		kind = ak_warning;
	else if (assertion->error)
		kind = ak_error;
	else
		kind = ak_debug;
	
	struct raw_assertion* rassertion = new_raw_assertion(kind, assertion->expression);
	
	raw_assertion_list_append(assertions, rassertion);
	
	free_raw_assertion(rassertion);
	
	EXIT;
}













