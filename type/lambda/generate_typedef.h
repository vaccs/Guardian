
struct type_queue;
struct type;

struct stringtree* lambda_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup);
