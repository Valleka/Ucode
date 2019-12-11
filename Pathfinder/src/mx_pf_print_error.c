#include "pathfinder.h"
        //
void mx_pf_print_error(t_err error, const char *s) {
        error == F_EXST ? mx_printerr("error: file "),
        mx_printerr(s), mx_printerr(" does not exist\n"):
        error == F_EMPT ? mx_printerr("error: file "),
        mx_printerr(s), mx_printerr(" is empty\n"):
        error == INVD_LN ? mx_printerr("error: line "),
        mx_printerr(s), mx_printerr(" is not valid\n"):
        mx_printerr("\n");
        exit(1);
}

void mx_pf_print_error_term(char *error_message) {
    mx_printerr(error_message);
    mx_printerr("\n");
    exit(1);
}
