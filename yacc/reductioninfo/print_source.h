
struct stringtree;

void reductioninfo_print_source(
	struct stringtree* tree,
	struct reductioninfo* this,
	struct structinfo* structinfo,
	struct type_cache* tcache,
	struct out_shared* shared,
	const char* grammar);
