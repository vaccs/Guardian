
struct type_cache;
struct type;

struct type* type_cache_get_dict_type(
	struct type_cache* this,
	struct type* key_type,
	struct type* value_type);
