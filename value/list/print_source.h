
struct environment_type;
struct value;
struct out_shared;

struct stringtree* list_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct environment_type* environment);
