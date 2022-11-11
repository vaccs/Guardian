
struct environment_type;
struct out_shared;

struct stringtree* let_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment);
