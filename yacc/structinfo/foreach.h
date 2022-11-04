
struct structinfo_node;
struct structinfo;

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(struct structinfo_node* ele));
