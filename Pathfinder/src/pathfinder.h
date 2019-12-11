#ifndef PATHFINDER_HDR
#define PATHFINDER_HDR
#include "libmx.h"

typedef enum e_err {
	F_EXST, 
	F_EMPT, 
	INVD_LN, 
} t_err;

typedef struct s_isl t_isl;
typedef struct s_link t_link;
typedef struct s_main t_main;
typedef struct s_path t_path;

struct s_isl {
	int index;
	char *name;
	t_link *links; //список всех связанных островов
	t_path **paths;
	t_isl *next;
};

struct s_link {
	int wdth_lnk; //вес между связанными островами
	t_isl *linked_isl;
	t_link *next;
};

struct s_main {
	int f_opn; //донор ридлайна
	int i_cnt; //к-во островов
	char *f_name; //имя файла
	char *l_ptr; //реципиент ридлайна
	t_isl *isl; //острова
	t_isl *start;//для файндера
	t_isl *end;//для файндера
	t_isl *start_remainder;//для файндера
	int weidth; //для файндреа
};

struct s_path {
	t_link *route; //путь
	int dist; // сумма дистанций всего пути
	  // истина, если дист-я пути мин. в этом списке путей
	bool is_shortest;
	t_path *next;
};

	//print pack
void mx_pf_print_error(t_err error, const char *s);
void mx_pf_print_error_term(char *error_message);
void mx_pf_print_all_paths(t_main *main);

	// main_pack
t_main *mx_pf_create_maine();
void mx_pf_prepare_for_algorithm(t_main *main);
	// links
t_link *mx_pf_create_link(t_isl *linked_isl);
void mx_pf_add_link(t_link **links, t_link *l);
void mx_pf_set_link(t_link **links, t_isl *linked_isl, int wdth_lnk);
void mx_pf_push_back_link(t_link **links, t_link *l);
void mx_pf_pop_back_link(t_link **links);
	// read file 
void mx_pf_read_file(t_main *main);// parse_file
t_isl *mx_pf_create_isl(char *name);
void mx_pf_add_isl(t_isl **islands, t_isl *i);
t_isl *mx_pf_get_isl(t_isl **islands, char *name);
	// finder pack
t_path *mx_pf_create_path(t_link *route);
void mx_pf_add_path(t_path **paths, t_path *p);
void mx_pf_find_all_paths(t_main *main);

#endif
