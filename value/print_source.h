
struct value_to_id;
struct environment_type;
struct value;
struct out_shared;

struct stringtree* value_print_source(
	struct value* this,
	struct out_shared* shared,
	struct value_to_id* vtoi);
