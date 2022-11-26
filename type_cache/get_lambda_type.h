
struct type_cache;
struct type_list;
struct type;

struct type* type_cache_get_lambda_type(
	struct type_cache* tcache,
	struct type_list* parameters,
	struct type* lambda_rettype);
