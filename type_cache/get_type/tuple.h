
struct type_cache;
struct type_list;

struct type* type_cache_get_tuple_type(
	struct type_cache* this,
	struct type_list* subtypes);
	
