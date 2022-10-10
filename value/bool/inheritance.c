
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance bool_value_inheritance = {
	.compare = compare_bool_value,
	.print = bool_value_print,
	.free = free_bool_value,
};

