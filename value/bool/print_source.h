
struct stringtree;
struct out_shared;
struct value_to_id;
struct environment_type;

unsigned bool_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi);
