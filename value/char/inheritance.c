
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance char_value_inheritance = {
	.print_source = char_value_print_source,
	
	.compare = compare_char_value,
	.print = char_value_print,
	.free = free_char_value,
};

