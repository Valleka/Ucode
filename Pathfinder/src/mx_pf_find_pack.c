#include "pathfinder.h"

static bool pf_is_visited(t_link *visited, t_isl *i) {
    t_link *iter = visited;

    if (!iter)
        return false;
    while (iter) {
        if (iter->linked_isl->name == i->name)
            return true;
        iter = iter->next;
    }
    return false;
}

static void pf_set_distances(t_path *path) {
    t_path *iter = path;
    t_link *rt;
    int dist;

    while (iter) {
        if (!iter->dist) {
            rt = iter->route;
            dist = 0;
            while (rt) {
                dist += rt->wdth_lnk;
                rt = rt->next;
            }
            iter->dist = dist;
            dist = 0;
        }
        iter = iter->next;
    }
}

static void pf_check_is_shortest(t_path *path) {
    t_path *iter = path;
    int min_dist = path->dist;

    while (iter) {
        if (iter->dist < min_dist)
            min_dist = iter->dist;
        iter->is_shortest = false;
        iter = iter->next;
    }
    iter = path;
    while (iter) {
        if (iter->dist == min_dist)
            iter->is_shortest = true;
        iter = iter->next;
    }
}

static void pf_find_path(t_main *main, t_link *visited, int weight, t_path **paths) {
    t_link *iter = main->start->links;
    t_link *visited_island = NULL;

    if (pf_is_visited(visited, main->start))
        return;
    visited_island = mx_pf_create_link(main->start);
    visited_island->wdth_lnk = weight;
    mx_pf_push_back_link(&visited, visited_island);
    if (main->start == main->end)
        mx_pf_add_path(&paths[main->end->index], mx_pf_create_path(visited));
    else
        while (iter) {
            main->start = iter->linked_isl;
            pf_find_path(main, visited, iter->wdth_lnk, paths);
            main->start = main->start_remainder;
            iter = iter->next;
        }
    mx_pf_pop_back_link(&visited);
}

void mx_pf_find_all_paths(t_main *main) {
    main->start = main->isl;
    t_link *visited = NULL;

    while (main->start) {
        main->end = main->start->next;
        main->start_remainder = main->start;
        while (main->end) {
            if (main->start != main->end) {
                pf_find_path(main, visited, 0, main->start->paths);
                main->start = main->start_remainder;
                pf_set_distances(main->start->paths[main->end->index]);
                pf_check_is_shortest(main->start->paths[main->end->index]);

            }
            main->end = main->end->next;
        }
        main->start = main->start->next;
    }
}
