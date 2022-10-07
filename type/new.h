
#include "kind.h"

struct type* new_type(
	unsigned id,
	enum type_kind kind,
	struct type_inheritance* inheritance,
	unsigned size);
