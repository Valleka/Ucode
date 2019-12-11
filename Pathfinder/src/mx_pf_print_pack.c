#include "pathfinder.h"

static t_link *pf_get_end_link(t_link *route) {
    t_link *iter = route;

    while (iter->next)
        iter = iter->next;
    return iter;
}

static void pf_print_route (t_link *route) {
    t_link *rt = route;

    mx_printstr("Route: ");
    while (rt) {
        if (rt->next) {
            mx_printstr(rt->linked_isl->name);
            mx_printstr(" -> ");
        }
        else
            mx_printstr(rt->linked_isl->name);
        rt = rt->next;
    }
    mx_printchar('\n');
}

static void pf_pritn_distance(t_link *route) {
    t_link *rt = route->next;
    int dist = 0;

    mx_printstr("Distance: ");
    if (!rt->next)
        mx_printint(rt->wdth_lnk);
    else
        while (rt) {//
            dist += rt->wdth_lnk;
            if (rt->next) {
                mx_printint(rt->wdth_lnk);
                mx_printstr(" + ");
            }
            else {
                mx_printint(rt->wdth_lnk);
                mx_printstr(" = ");
                mx_printint(dist);
            }
            rt = rt->next;
        }
    mx_printchar('\n');
}

    //печатаем маршрут
 static void pf_print_paths(t_path *path) {
    t_path *p = path;
    t_link *end_link;

    while (p) {
        if (p->is_shortest) {
            end_link = pf_get_end_link(p->route);
            mx_printstr("========================================\n");
            mx_printstr("Path: ");
            mx_printstr(p->route->linked_isl->name);
            mx_printstr(" -> ");
            mx_printstr(end_link->linked_isl->name);
            mx_printstr("\n");
            pf_print_route(p->route);
            pf_pritn_distance(p->route);
            mx_printstr("========================================\n");
        }
        p = p->next;
    }
}

    //печатаем все маршруты
void mx_pf_print_all_paths(t_main *main) {
    t_isl *isl = main->isl;
    t_path *pth;

    while (isl) {
        for (int i = 0; i < main->i_cnt; i++) {
            pth = isl->paths[i];
            if (pth)
                pf_print_paths(pth);
        }
        isl = isl->next;
    }
}
