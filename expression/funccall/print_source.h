
struct environment_type;
struct expression;
struct out_shared;

struct stringtree* funccall_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment);
