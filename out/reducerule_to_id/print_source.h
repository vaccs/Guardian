
#include <stdio.h>

struct reducerule_to_id;
struct string_to_id;

struct stringtree* reducerule_to_id_print_source(
	struct type_cache* tcache,
	struct reducerule_to_id* this,
	struct string_to_id* stoi,
	struct out_shared* shared);
