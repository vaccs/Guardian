
struct type;
struct environment_type;
struct out_shared;
struct expression;

struct stringtree* fieldaccess_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment);
