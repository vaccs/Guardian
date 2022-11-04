
struct type_cache;
struct type;

struct type* type_cache_get_list_type(
	struct type_cache* this,
	struct type* element_type);
