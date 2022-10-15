
#include "kind.h"

struct funcdata* new_funcdata(
	enum funcdata_kind kind,
	struct type* type,
	struct lambda_expression* lexpression,
	unsigned id);
