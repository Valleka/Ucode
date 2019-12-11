#include "pathfinder.h"

t_path *mx_pf_create_path(t_link *route) {
    t_path *path = malloc(sizeof(t_path));
    t_link *iter = route;
    t_link *ptr;

    path->route = mx_pf_create_link(route->linked_isl);
    path->route->wdth_lnk = route->wdth_lnk;
    path->next = NULL;
    ptr = path->route;
    while (iter->next) {
        ptr->next = mx_pf_create_link(iter->next->linked_isl);
        ptr->next->wdth_lnk = iter->next->wdth_lnk;
        ptr = ptr->next;
        iter = iter->next;
    }
    return path;
}

void mx_pf_add_path(t_path **paths, t_path *p) {
    if (!*paths) {
        *paths = p;
        return;
    }
    p->next = *paths;
    *paths = p;
}
