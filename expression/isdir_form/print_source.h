
struct environment_type;
struct expression;
struct out_shared;

struct stringtree* isdir_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment);
