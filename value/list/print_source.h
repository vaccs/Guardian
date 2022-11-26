
struct stringtree;
struct value_to_id;
struct environment_type;
struct value;
struct out_shared;

unsigned list_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi);
