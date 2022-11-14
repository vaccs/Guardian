
#include <stdbool.h>

struct value;
struct value_to_id;

bool value_to_id_add(
	struct value_to_id* this,
	unsigned *out_id,
	struct value* value);
