
struct environment_type;
struct assertion;
struct out_shared;

struct stringtree* assertion_print_source(
	struct assertion* this,
	struct out_shared* shared,
	struct environment_type* environment);
