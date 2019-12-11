#include "pathfinder.h"

t_isl *mx_pf_create_isl(char *name) {
    t_isl *isl = malloc(sizeof(t_isl));

    isl->links = NULL;
    isl->name = name;
    isl->next = NULL;
    return isl;
}

void mx_pf_add_isl(t_isl **islands, t_isl *i) {
    if (!*islands) {
        *islands = i;
        return;
    }
    i->next = *islands;
    *islands = i;
}

t_isl *mx_pf_get_isl(t_isl **islands, char *name) {
    t_isl *iter = *islands;
    t_isl *last_isl;

    if (!iter) {
        *islands = mx_pf_create_isl(name);
        return *islands;
    }
    while (iter) {
        if (mx_strcmp(iter->name, name) == 0) {
            mx_strdel(&name);
            return iter;
        }
        if (iter->next == NULL)
            last_isl = iter;
        iter = iter->next;
    }
    last_isl->next = mx_pf_create_isl(name);
    return last_isl->next;
}
