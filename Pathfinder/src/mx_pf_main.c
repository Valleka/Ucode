#include "pathfinder.h"

t_main *mx_pf_create_maine() {
    t_main *main = malloc(sizeof(t_main));

	main->f_name = NULL;
	main->isl = NULL;
	main->l_ptr = NULL;
	main->start = NULL;
	main->end = NULL;
	main->start_remainder = NULL;
    return main;
}

void mx_pf_prepare_for_algorithm(t_main *main) {
    t_isl *iter = main->isl;
    int i = 0;

    while (iter) {
        iter->index = i;
        iter->paths = malloc(sizeof(t_path *) * main->i_cnt);
		for (int i = 0; i < main->i_cnt; i++)
			iter->paths[i] = NULL;
        i++;
        iter = iter->next;
    }
}

static void reverse(t_path **head_ref) {
    t_path *prev = NULL;
    t_path *current = *head_ref;
    t_path *next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

static void reverse_paths(t_main *main) {
    t_isl *isl = main->isl;

    while (isl) {
        for (int i = 0; i < main->i_cnt; i++)
            reverse(&(isl->paths[i]));
        isl = isl->next;
    }
}


int main(int argc, char **argv) {
	int f_opn;
	t_main *mn;
	
	if (argc != 2)
        mx_pf_print_error_term("usage: ./pathfinder [filename]");
	f_opn = open(argv[1], O_RDONLY);
	if (read(f_opn, 0, 0) < 0)
		mx_pf_print_error(F_EXST, argv[1]);
	mn = mx_pf_create_maine();
	mn->f_name = argv[1];
	mn->f_opn = f_opn;
	mx_pf_read_file(mn);
    mx_pf_prepare_for_algorithm(mn);
    mx_pf_find_all_paths(mn);
	reverse_paths(mn);
	mx_pf_print_all_paths(mn);
	return 0;
}
