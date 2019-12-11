#include "pathfinder.h"

t_link *mx_pf_create_link(t_isl *linked_isl) {
    t_link *lnk = malloc(sizeof(t_link));

    lnk->linked_isl = linked_isl;
    lnk->next = NULL;
    return lnk;
}

void mx_pf_add_link(t_link **links, t_link *l) {
    if (!links) {
        *links = l;
        return;
    }
    l->next = *links;
    *links = l;
}

void mx_pf_push_back_link(t_link **links, t_link *l) {
    t_link *iter = *links;

    if (!*links) {
        *links = l;
        return;
    }
    while (iter->next) {
        iter = iter->next;
    }
    iter->next = l;
}

void mx_pf_pop_back_link(t_link **links) {
    t_link *l = *links;

    if (*links != NULL) {
        if (l->next == NULL) {
            l->linked_isl = NULL;
            free(l);
        } 
        else {
            while (l->next->next)
                l = l->next;
            l->next->linked_isl = NULL;
            free(l->next);
            l->next = NULL;
        }
    }
}

void mx_pf_set_link(t_link **links, t_isl *linked_isl, int wdth_lnk) {
    t_link *iter = *links;
    t_link *last_link;

    if (!iter) {
        *links = mx_pf_create_link(linked_isl);
        (*links)->wdth_lnk = wdth_lnk;
        return;
    }
    while (iter) {
        if (linked_isl == iter->linked_isl)
            return;
        if (iter->next == NULL)
            last_link = iter;
        iter = iter->next;
    }
    last_link->next = mx_pf_create_link(linked_isl);
    last_link->next->wdth_lnk = wdth_lnk;
    return;
}
