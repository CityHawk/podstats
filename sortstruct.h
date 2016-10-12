typedef struct _obj {
    int count;
    char name[256];
} obj;

void o_add(obj o[], char *name);
void o_print(obj o[]);
void sort_by_name(obj o[]);

obj *_find_elem_by_name(obj o[],char *name);
