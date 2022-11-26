
struct type;
struct out_shared;
struct environment_type;
struct statement;

struct stringtree* declare_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct type* environment_type);
