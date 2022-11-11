
struct environment_type;
struct value;
struct out_shared;

struct stringtree* value_print_source(
	struct value* this,
	struct out_shared* shared,
	struct environment_type* environment);
