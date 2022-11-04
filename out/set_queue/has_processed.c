
#include <debug.h>

#include "struct.h"
#include "has_processed.h"

bool set_queue_has_processed(
	struct set_queue* this,
	struct string* grammar)
{
	return stringset_contains(this->queued, grammar);
}

