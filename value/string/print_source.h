
struct stringtree;
struct value_to_id;
struct out_shared;
struct environment_type;

unsigned string_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi);
