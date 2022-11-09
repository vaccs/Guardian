
struct type;
struct type_queue;

struct stringtree* environment_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup);
