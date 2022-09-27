
#include "kind.h"

struct type* new_type(
	enum type_kind kind,
	struct type_inheritance* inheritance,
	unsigned size);
