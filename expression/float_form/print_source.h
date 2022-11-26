
struct type;
struct environment_type;
struct expression;
struct out_shared;

struct stringtree* float_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment);
