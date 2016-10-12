#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortstruct.h"

static int _o_count;

void o_add(obj o[], char *name) {

    obj *_t;

    if ((_t = _find_elem_by_name(o, name)) != NULL) {
        _t->count++;
    } else {
        strcpy(o[_o_count].name, name);
        o[_o_count].count = 1;
        _o_count++;
    }
}

obj *_find_elem_by_name(obj o[], char *name) {
    for (int i = 0; i < _o_count; i++) {
        if (strcmp(name, o[i].name) == 0) {
                return &o[i];
        }
    }
    return NULL;
}

void o_print(obj *o) {
    for (int i = 0; i < _o_count; i++) {
        printf("%s = %d\n", o[i].name, o[i].count);
    }
}

void sort_by_name(obj *o) {
    for (int i=0; i < _o_count; i++) {
        for (int j=i+1; j < _o_count; j++) {
            if (strcmp(o[j].name, o[i].name) < 0) {
                obj tmp;
                tmp = o[i];
                o[i] = o[j];
                o[j] = tmp;
            }
        }
    }
}
