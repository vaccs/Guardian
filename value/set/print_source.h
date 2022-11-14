
struct value_to_id;
struct environment_type;
struct value;
struct out_shared;

struct stringtree* set_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi);
