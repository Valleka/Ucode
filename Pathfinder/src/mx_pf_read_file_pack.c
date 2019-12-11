#include "pathfinder.h"

int mx_atoi(const char *str) {
    int i = -1;
    int result = 0;

    while (str[++i]) {
        if (mx_isdigit(str[i]))
            result = result * 10 + str[i] - '0';
        if (!mx_isdigit(str[i]))
            return result;
    }
    return result;
}

    //check_first_line
static void pf_verify_fst_line(t_main *main) {
    if (main->l_ptr == NULL)
        mx_pf_print_error(F_EMPT, main->f_name);
    if (mx_isnumber(main->l_ptr)) {
        main->i_cnt = mx_atoi(main->l_ptr);
        mx_strdel(&main->l_ptr);
    }
    else
        mx_pf_print_error_term("error: line 1 is not valid");
}

    // check_line
static bool pf_verify_line(char *line) {
    int i = -1;
    int isl_1 = 0;
    int isl_2 = 0;

    if (mx_strcmp(line, "") == 0)
        return false;
    while (mx_isalpha(line[++i]))
        isl_1++;
    if (line[i] != '-')
        return false;
    while (mx_isalpha(line[++i]))
        isl_2++;
    if (!isl_1 || !isl_2)
        return false;
    if (line[i++] != ',')
        return false;
    if (!(line[i]) || !mx_isnumber(line + i))
        return false;
    return true;
}

    //parse line
static void pf_read_line(t_main *main) {
    char **ptr;
    char *ptr_1;
    t_isl *isl_1;
    t_isl *isl_2;
    int wdth_lnk;

    ptr = mx_strsplit(main->l_ptr, '-');
    isl_1 = mx_pf_get_isl(&main->isl, mx_strdup(ptr[0]));
    ptr_1 = mx_strdup(ptr[1]);
    mx_del_strarr(&ptr);
    ptr = mx_strsplit(ptr_1, ',');
    mx_strdel(&ptr_1);
    isl_2 = mx_pf_get_isl(&main->isl, mx_strdup(ptr[0]));
    wdth_lnk = mx_atoi(ptr[1]);
    mx_del_strarr(&ptr);
    mx_pf_set_link(&isl_1->links, isl_2, wdth_lnk);
    mx_pf_set_link(&isl_2->links, isl_1, wdth_lnk);
}

static void pf_check_isl_count(t_main *main) {
    t_isl *iter = main->isl;
    int count = 0;

    while (iter) {
        count++;
        iter = iter->next;
    }
    if (main->i_cnt != count)
        mx_pf_print_error_term("error: invalid number of islands");
}

    //parse file
void mx_pf_read_file(t_main *main) {
    int line = 2;

    mx_read_line(&main->l_ptr, 128, '\n', main->f_opn);
    pf_verify_fst_line(main);
    while (mx_read_line(&main->l_ptr, 128, '\n', main->f_opn) >= 0) {
        if (pf_verify_line(main->l_ptr))
            pf_read_line(main);
        else
            mx_pf_print_error(INVD_LN, mx_itoa(line));
        mx_strdel(&main->l_ptr);
        line++;
    }
    pf_check_isl_count(main);
}
