
struct zebu_type;
struct type_cache;

struct type* build_primitive_type(
	struct type_cache* tcache,
	struct zebu_primitive_type* type);

struct type* build_type(
	struct type_cache* tcache,
	struct zebu_type* type);
	
