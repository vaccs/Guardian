
struct type;
struct environment_type;
struct expression;
struct out_shared;

struct stringtree* expression_print_source(
	struct expression* this,
	struct out_shared* shared,
	struct type* environment);
