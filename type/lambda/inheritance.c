
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef_text.h"
#include "generate_free_text.h"
#include "compare.h"
#include "free.h"

struct type_inheritance lambda_type_inheritance = {
	.generate_typedef_text = lambda_type_generate_typedef_text,
	.generate_free_text = lambda_type_generate_free_text,
	.compare = compare_lambda_types,
	.free = free_lambda_type,
};

